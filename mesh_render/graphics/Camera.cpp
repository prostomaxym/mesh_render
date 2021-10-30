#include "Camera.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <glut.h>

#include "../main.h"

Camera::Camera()
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->camspeed = 1.0f;
	this->vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

Camera::Camera(float camspd)
{
	this->fPitch = 0.0f;
	this->fYaw = 0.0f;
	this->camspeed = camspd;
	this->vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

Camera::Camera(vec3f cameraPos = { 0.0f, 0.0f, 0.0f }, 
							 float yaw = 0.0f, float pitch = 0.0f, float camspd = 1.0f)
{
	yaw *= M_PI / 180.0f;
	pitch *= M_PI / 180.0f;
	this->fPitch = pitch;
	this->fYaw = yaw;
	this->camspeed = camspd;
	this->vCamera = cameraPos;
	this->vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	this->update();
}

void Camera::update()
{
	vUp = { 0.0f, 1.0f, 0.0f };
	vTarget = { 0.0f, 0.0f, 0.0f };

	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	vLookDir.normalise();

	vRight = vUp ^ vLookDir;
	vRight.normalise();

	vTarget = vCamera + vLookDir;
}

void Camera::setAngle(float yaw, float pitch)
{
	this->fYaw += yaw;
	this->fPitch -= pitch;

	if (this->fPitch > 1.57f)
	{
		this->fPitch = 1.57f;
	}
	else if (this->fPitch < -1.57f)
	{
		this->fPitch = -1.57f;
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
	vRight = vRight * (camspeed * dt);
	this->vCamera = vCamera + vRight;
}

void Camera::moveRight()
{
	vRight = vRight * (camspeed * dt);
	this->vCamera = vCamera - vRight;
}

void Camera::moveForward()
{
	vLookDir = vLookDir * (camspeed * dt);
	this->vCamera = vCamera + vLookDir;
}

void Camera::moveBackward()
{
	vLookDir = vLookDir * (camspeed * dt);
	this->vCamera = vCamera - vLookDir;
}

void Camera::moveUp()
{
	vUp = vUp * (dt * camspeed);
	this->vCamera = vCamera +  vUp;
}

void Camera::moveDown() 
{
	vUp = vUp * (dt * camspeed);
	this->vCamera = vCamera - vUp;
}