#ifndef MESH_RENDER_MATRIX_H_
#define MESH_RENDER_MATRIX_H_

#include "Vector.h"

struct mat4x4
{
	float m[4][4] = { 0 };

	mat4x4 operator*(mat4x4& other);

	void makeIdentity();
	void rotateX(float fAngleRad);
	void rotateY(float fAngleRad);
	void rotateZ(float fAngleRad);
	void makeTranslation(float x, float y, float z);
	void makeProjection(float fNear, float fFar, float fFov);
};

extern mat4x4 matProj, matRotX, matRotY, matRotZ, matWorld, matTrans;

vec3f MatrixMultiplyVector(mat4x4& m, vec3f& i);

#endif  // MESH_RENDER_MATRIX_H_
