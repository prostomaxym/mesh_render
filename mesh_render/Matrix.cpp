#include "Matrix.h"

#include <cmath>

#include <glut.h>

mat4x4 matProj, matRotX, matRotY,matRotZ, matWorld, matTrans;

mat4x4 mat4x4::operator*(mat4x4& other)
{
	mat4x4 matrix;
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			matrix.m[r][c] = this->m[r][0] * other.m[0][c] + this->m[r][1] * other.m[1][c]
				+ this->m[r][2] * other.m[2][c] + this->m[r][3] * other.m[3][c];
		}
	}
	return matrix;
}
void mat4x4::makeProjection(float fNear, float fFar, float fFov)
{
	float fAspectRatio = (float)glutGet(GLUT_WINDOW_HEIGHT) / (float)glutGet(GLUT_WINDOW_WIDTH);
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;
}

void mat4x4::makeIdentity()
{
	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
}

void mat4x4::rotateX(float fAngleRad)
{
	this->m[0][0] = 1.0f;
	this->m[1][1] = cosf(fAngleRad);
	this->m[1][2] = sinf(fAngleRad);
	this->m[2][1] = -sinf(fAngleRad);
	this->m[2][2] = cosf(fAngleRad);
	this->m[3][3] = 1.0f;
}

void mat4x4::rotateY(float fAngleRad)
{
	this->m[0][0] = cosf(fAngleRad);
	this->m[0][2] = sinf(fAngleRad);
	this->m[2][0] = -sinf(fAngleRad);
	this->m[1][1] = 1.0f;
	this->m[2][2] = cosf(fAngleRad);
	this->m[3][3] = 1.0f;
}

void mat4x4::rotateZ(float fAngleRad)
{
	this->m[0][0] = cosf(fAngleRad);
	this->m[0][1] = sinf(fAngleRad);
	this->m[1][0] = -sinf(fAngleRad);
	this->m[1][1] = cosf(fAngleRad);
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
}

void mat4x4::makeTranslation(float x, float y, float z)
{
	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
	this->m[3][0] = x;
	this->m[3][1] = y;
	this->m[3][2] = z;
}

vec3f MatrixMultiplyVector(mat4x4& m, vec3f& i)
{
	vec3f v;
	v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	return v;
}