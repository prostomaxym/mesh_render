#ifndef MESH_RENDER_GRAPHICS_MATRIX_H_
#define MESH_RENDER_GRAPHICS_MATRIX_H_

#include "Vector.h"

#include "../glatter/glatter.h"

struct mat4
{
	GLfloat m[4][4] = { 0.0f };

	mat4 operator*(mat4& other);

	void makeIdentity();
	void rotateX(float fAngleRad);
	void rotateY(float fAngleRad);
	void rotateZ(float fAngleRad);
	void translate(float x, float y, float z);
	void convertArrayToMatrix(GLfloat a[16]);
};

void invertMatrix(GLfloat(&m)[16], GLfloat(&inv)[16]);
void transposeMatrix(GLfloat* src, GLfloat* dst, const int N, const int M);
#endif  // MESH_RENDER_GRAPHICS_MATRIX_H_
