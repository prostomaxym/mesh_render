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
	Light(vec3f lightPos, vec3f viewPos, vec3f color);

	void initLight(Shader& shader, Camera& cam);
	void updateLight(Shader& shader, Camera& cam);

private:
	vec3f lightPos_;
	vec3f viewPos_;
	vec3f lightColor_;

	GLuint lightPosUniform_;
	GLuint viewPosUniform_;
	GLuint lightColorUniform_;
};
#endif  // MESH_RENDER_GRAPHICS_LIGHT_H_