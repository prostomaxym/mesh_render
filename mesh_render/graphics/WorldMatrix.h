#ifndef MESH_RENDER_GRAPHICS_WORLDMATRIX_H_
#define MESH_RENDER_GRAPHICS_WORLDMATRIX_H_

#include "Matrix.h"
#include "Shader.h"

class WorldMatrix
{
public:
	WorldMatrix();

	void init(Shader& shader);
	void update(Shader& shader);

	void translate(Shader& shader, float x, float y, float z);
	void rotate(Shader& shader, float angle, vec3f vRotateAround);
	void scale(Shader& shader,  float scaleX, float scaleY, float scaleZ);
private:
	mat4 matProj;
	mat4 matModelView;
	mat4 MVP;

	GLuint MVPmatUniform;
};
#endif  // MESH_RENDER_GRAPHICS_WORLDMATRIX_H_
