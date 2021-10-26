#include "Vector.h"

#include <cmath>

vec3f vec3f::operator+(vec3f& other)
{
	return { this->x + other.x,this->y + other.y, this->z + other.z };
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
	return sqrtf((*this) * (*this));
}

void vec3f::normalise()
{
	float l = this->getLength();
	this->x /= l;
	this->y /= l;
	this->z /= l;
}