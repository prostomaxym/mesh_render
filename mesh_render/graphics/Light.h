#ifndef MESH_RENDER_GRAPHICS_LIGHT_H_
#define MESH_RENDER_GRAPHICS_LIGHT_H_

#include "Camera.h"
#include "Shader.h"
#include "Vector.h"

#include "../glatter/glatter.h"

class Light
{
public:
	Light();
	Light(vec3f lightPos, float power, vec3f color, float period);
	Light(float distance, float power, vec3f color, float zOffset, float period);

	void initLight(Shader& shader, Camera& cam);

	vec3f getLightPos();

	void updateStaticLight(Shader& shader, Camera& cam);
	void updateDynamicLight(Shader& shader, Camera& cam);

private:
	vec3f lightPos_;
	vec3f viewPos_;
	vec3f lightColor_;
	float lightPower_;
	float lightDistance_;
	float dayPeriod_;

	GLuint lightPosUniform_;
	GLuint viewPosUniform_;
	GLuint lightColorUniform_;
	GLuint lightPowerUniform_;
};
#endif  // MESH_RENDER_GRAPHICS_LIGHT_H_