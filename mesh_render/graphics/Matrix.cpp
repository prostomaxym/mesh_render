#include "Matrix.h"

#include <cmath>



mat4 mat4::operator*(mat4& other)
{
	mat4 matrix;
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
		{
			matrix.m[r][c] = this->m[r][0] * other.m[0][c] + this->m[r][1] * other.m[1][c] +
				this->m[r][2] * other.m[2][c] + this->m[r][3] * other.m[3][c];
		}
	return matrix;
}

void mat4::makeIdentity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;	m[1][3] = 0.0f;
	m[2][0] = 0.0f;	m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void mat4::rotateX(float fAngleRad)
{
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[1][2] = sinf(fAngleRad);
	matrix.m[2][1] = -sinf(fAngleRad);
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	mat4 temp = *this;
	*this = temp * matrix;
}

void mat4::rotateY(float fAngleRad)
{
	mat4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][2] = sinf(fAngleRad);
	matrix.m[2][0] = -sinf(fAngleRad);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(fAngleRad);
	matrix.m[3][3] = 1.0f;
	mat4 temp = *this;
	*this = temp * matrix;
}

void mat4::rotateZ(float fAngleRad)
{
	mat4 matrix;
	matrix.m[0][0] = cosf(fAngleRad);
	matrix.m[0][1] = sinf(fAngleRad);
	matrix.m[1][0] = -sinf(fAngleRad);
	matrix.m[1][1] = cosf(fAngleRad);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	mat4 temp = *this;
	*this = temp * matrix;
}

void mat4::translate(float x, float y, float z)
{
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	matrix.m[3][2] = z;
	mat4 temp = *this;
	*this = temp * matrix;
}

void mat4::convertArrayToMatrix(GLfloat a[16])
{
	m[0][0] = a[0];  m[0][1] = a[1];  m[0][2] = a[2];  m[0][3] = a[3];
	m[1][0] = a[4];  m[1][1] = a[5];  m[1][2] = a[6];  m[1][3] = a[7];
	m[2][0] = a[8];  m[2][1] = a[9];  m[2][2] = a[10]; m[2][3] = a[11];
	m[3][0] = a[12]; m[3][1] = a[13]; m[3][2] = a[14]; m[3][3] = a[15];
}