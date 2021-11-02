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

private:
	mat4 matProj;
	mat4 matModelView;
	mat4 MVP;

	GLuint MVPmatUniform;
};
#endif  // MESH_RENDER_GRAPHICS_WORLDMATRIX_H_
