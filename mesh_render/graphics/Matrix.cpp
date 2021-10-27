#include "Matrix.h"

#include <cmath>

#include <glut.h>

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

	this->m[0][0] = fAspectRatio * fFovRad;
	this->m[1][1] = fFovRad;
	this->m[2][2] = fFar / (fFar - fNear);
	this->m[3][2] = (-fFar * fNear) / (fFar - fNear);
	this->m[2][3] = 1.0f;
	this->m[3][3] = 0.0f;
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

void mat4x4::MatrixPointAt(vec3f& pos, vec3f& target, vec3f& up)
{
	// Calculate new forward direction
	vec3f newForward = target - pos;
	newForward.normalise();

	// Calculate new Up direction
	vec3f a = newForward * (up * newForward);
	vec3f newUp = up - a;
	newUp.normalise();

	// New Right direction is easy, its just cross product
	vec3f newRight = newUp ^ newForward;

	// Construct Dimensioning and Translation Matrix	
	this->m[0][0] = newRight.x;		this->m[0][1] = newRight.y;		this->m[0][2] = newRight.z;	this->m[0][3] = 0.0f;
	this->m[1][0] = newUp.x;			this->m[1][1] = newUp.y;			this->m[1][2] = newUp.z;		this->m[1][3] = 0.0f;
	this->m[2][0] = newForward.x;	this->m[2][1] = newForward.y;	this->m[2][2] = newForward.z;this->m[2][3] = 0.0f;
	this->m[3][0] = pos.x;				this->m[3][1] = pos.y;				this->m[3][2] = pos.z;			this->m[3][3] = 1.0f;
}

void mat4x4::MatrixQuickInverse(mat4x4& m) // Only for Rotation/Translation Matrices
{
	this->m[0][0] = m.m[0][0]; this->m[0][1] = m.m[1][0]; this->m[0][2] = m.m[2][0]; this->m[0][3] = 0.0f;
	this->m[1][0] = m.m[0][1]; this->m[1][1] = m.m[1][1]; this->m[1][2] = m.m[2][1]; this->m[1][3] = 0.0f;
	this->m[2][0] = m.m[0][2]; this->m[2][1] = m.m[1][2]; this->m[2][2] = m.m[2][2]; this->m[2][3] = 0.0f;
	this->m[3][0] = -(m.m[3][0] * this->m[0][0] + m.m[3][1] * this->m[1][0] + m.m[3][2] * this->m[2][0]);
	this->m[3][1] = -(m.m[3][0] * this->m[0][1] + m.m[3][1] * this->m[1][1] + m.m[3][2] * this->m[2][1]);
	this->m[3][2] = -(m.m[3][0] * this->m[0][2] + m.m[3][1] * this->m[1][2] + m.m[3][2] * this->m[2][2]);
	this->m[3][3] = 1.0f;
}