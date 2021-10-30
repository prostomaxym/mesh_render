#include "Camera.h"

#include <cmath>

#include "../main.h"

void Camera::init()
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->movespeed = 0.5f;
}

void Camera::init(float movespd)
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->movespeed = movespd;
}


void Camera::update()
{
	vForward = vLookDir * (movespeed * dt);
	vSide = vUp ^ vForward;
	vUp = { 0.0f, 1.0f, 0.0f };
	vTarget = { 0.0f, 0.0f, 0.0f };
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	vTarget = vCamera + vLookDir;
}