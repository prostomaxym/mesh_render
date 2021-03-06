#include "Vector.h"

#include <cmath>

vec3f::vec3f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

vec3f::vec3f(float b)
{
	x = b;
	y = b;
	z = b;
	w = 1.0f;
}

vec3f::vec3f(const float* b)
{
	x = b[0];
	y = b[1];
	z = b[2];
	w = 1.0f;
}

vec3f::vec3f(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
	w = 1.0f;
}
vec3f vec3f::operator+(vec3f& other)
{
	return { this->x + other.x, this->y + other.y, this->z + other.z };
}

vec3f vec3f::operator-(vec3f& other)
{
	return { this->x - other.x,this->y - other.y, this->z - other.z };
}

vec3f vec3f::operator*(float k)
{
	return { this->x*k,this->y*k,this->z*k };
}

vec3f vec3f::operator/(float k)
{
	if (k != 0)
	{
		return { this->x / k,this->y / k,this->z / k };
	}
	else
	{
		return { this->x, this->y, this->z };
	}
}

float vec3f::operator*(vec3f& other)
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

vec3f vec3f::operator^(vec3f& other)
{
	vec3f v;
	v.x = this->y * other.z - this->z * other.y;
	v.y = this->z * other.x - this->x * other.z;
	v.z = this->x * other.y - this->y * other.x;
	return v;
}

float vec3f::getLength()
{
	return sqrtf(x * x + y * y + z * z);
}

void vec3f::normalise()
{
	float l = this->getLength();
	this->x /= l;
	this->y /= l;
	this->z /= l;
}

void vec3f::intersectPlane(vec3f& plane_p, vec3f& plane_n, vec3f& lineStart, vec3f& lineEnd, float& t)
{
	plane_n.normalise();
	float plane_d = -1.0f * (plane_n * plane_p);
	float ad = lineStart * plane_n;
	float bd = lineEnd * plane_n;
	t = (-plane_d - ad) / (bd - ad);
	vec3f lineStartToEnd = lineEnd - lineStart;
	vec3f lineToIntersect = lineStartToEnd * t;
	*this = lineStart + lineToIntersect;
}