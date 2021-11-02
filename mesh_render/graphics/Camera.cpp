#include "Camera.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <glut.h>

#include "../main.h"

Camera::Camera()
{
	fPitch_ = 0.0f;
	fYaw_ = 0.0f;
	camspeed_ = 1.0f;
	vLookDir_ = { cosf(fPitch_) * cosf(fYaw_), sinf(fPitch_) , cosf(fPitch_) * sinf(fYaw_) };
	update();
}

Camera::Camera(float camspd)
{
	fPitch_ = 0.0f;
	fYaw_ = 0.0f;
	camspeed_ = camspd;
	vLookDir_ = { cosf(fPitch_) * cosf(fYaw_), sinf(fPitch_) , cosf(fPitch_) * sinf(fYaw_) };
	update();
}

Camera::Camera(vec3f cameraPos = { 0.0f, 0.0f, 0.0f }, 
							 float yaw = 0.0f, float pitch = 0.0f, float camspd = 1.0f)
{
	yaw *= M_PI / 180.0f;
	pitch *= M_PI / 180.0f;
	fPitch_ = pitch;
	fYaw_ = yaw;
	camspeed_ = camspd;
	vCamera_ = cameraPos;
	vLookDir_ = { cosf(fPitch_) * cosf(fYaw_), sinf(fPitch_) , cosf(fPitch_) * sinf(fYaw_) };
	update();
}

void Camera::update()
{
	vUp_ = { 0.0f, 1.0f, 0.0f };
	vTarget_ = { 0.0f, 0.0f, 0.0f };

	vLookDir_ = { cosf(fPitch_) * cosf(fYaw_), sinf(fPitch_) , cosf(fPitch_) * sinf(fYaw_) };
	vLookDir_.normalise();

	vRight_ = vUp_ ^ vLookDir_;
	vRight_.normalise();

	vTarget_ = vCamera_ + vLookDir_;
}

void Camera::setAngle(float yaw, float pitch)
{
	fYaw_ += yaw;
	fPitch_ -= pitch;

	if (fPitch_ > 1.57f)
	{
		fPitch_ = 1.57f;
	}
	else if (fPitch_ < -1.57f)
	{
		fPitch_ = -1.57f;
	}
}

void Camera::lookAt()
{
	gluLookAt(
		vCamera_.x,	vCamera_.y, vCamera_.z,
		vTarget_.x, vTarget_.y, vTarget_.z,
		vUp_.x,			vUp_.y,			vUp_.z );
}

void Camera::moveLeft()
{
	vRight_ = vRight_ * (camspeed_ * dt);
	vCamera_ = vCamera_ + vRight_;
}

void Camera::moveRight()
{
	vRight_ = vRight_ * (camspeed_ * dt);
	vCamera_ = vCamera_ - vRight_;
}

void Camera::moveForward()
{
	vLookDir_ = vLookDir_ * (camspeed_ * dt);
	vCamera_ = vCamera_ + vLookDir_;
}

void Camera::moveBackward()
{
	vLookDir_ = vLookDir_ * (camspeed_ * dt);
	vCamera_ = vCamera_ - vLookDir_;
}

void Camera::moveUp()
{
	vUp_ = vUp_ * (camspeed_ * dt);
	vCamera_ = vCamera_ +  vUp_;
}

void Camera::moveDown() 
{
	vUp_ = vUp_ * (camspeed_ * dt);
	vCamera_ = vCamera_ - vUp_;
}

vec3f Camera::getCameraPos()
{
	return vCamera_;
}