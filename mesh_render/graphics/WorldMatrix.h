#ifndef MESH_RENDER_GRAPHICS_WORLDMATRIX_H_
#define MESH_RENDER_GRAPHICS_WORLDMATRIX_H_

#include "Matrix.h"
#include "Shader.h"
#include "Vector.h"

class WorldMatrix
{
public:
	WorldMatrix();

	void init(Shader& shader);
	void update(Shader& shader);

	void translate(Shader& shader, vec3f vTranslate);
	void rotate(Shader& shader, float angle, vec3f vRotateAround);
	void scale(Shader& shader,  vec3f vScale);

private:
	mat4 matProj;
	mat4 matModelView;
	mat4 MVP;

	GLuint MVPmatUniform;
};
#endif  // MESH_RENDER_GRAPHICS_WORLDMATRIX_H_
