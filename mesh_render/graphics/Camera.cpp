#include "Camera.h"

#include <cmath>

#include <glut.h>

#include "../main.h"

Camera::Camera()
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->camspeed = 1.0f;
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

Camera::Camera(float camspd)
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->camspeed = camspd;
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

Camera::Camera(vec3f cameraPos = { 0.0f, 0.0f, 0.0f }, 
							 float pitch = 0.0f, float yaw = 0.0f, float camspd = 1.0f)
{
	this->fPitch = pitch;
	this->fYaw = yaw;
	this->camspeed = camspd;
	this->vCamera = cameraPos;
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

void Camera::update()
{
	vUp = { 0.0f, 1.0f, 0.0f };
	vTarget = { 0.0f, 0.0f, 0.0f };
	vForward = vLookDir * (camspeed * dt);
	vSide = vUp ^ vForward;
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	vTarget = vCamera + vLookDir;
}

void Camera::setAngle(float yaw, float pitch)
{
	this->fYaw += yaw;
	this->fPitch -= pitch;

	if (this->fPitch > 1.57f)
	{
		this->fPitch = 1.56f;
	}
	else if (this->fPitch < -1.57f)
	{
		this->fPitch = -1.56f;
	}
}

void Camera::lookAt()
{
	gluLookAt(
		this->vCamera.x, this->vCamera.y, this->vCamera.z,
		this->vTarget.x, this->vTarget.y, this->vTarget.z,
		this->vUp.x,		 this->vUp.y,			this->vUp.z );
}

void Camera::moveLeft()
{
	this->vCamera = this->vCamera + this->vSide;
}

void Camera::moveRight()
{
	this->vCamera = this->vCamera - this->vSide;
}

void Camera::moveForward()
{
	this->vCamera = this->vCamera + this->vForward;
}

void Camera::moveBackward()
{
	this->vCamera = this->vCamera - this->vForward;
}

void Camera::moveUp()
{
	this->vCamera = this->vCamera + this->vUp;
}

void Camera::moveDown() 
{
	this->vCamera = this->vCamera - this->vUp;
}