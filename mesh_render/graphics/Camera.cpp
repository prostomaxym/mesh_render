#include "Camera.h"

#include <cmath>

#include "../main.h"

void Camera::update(float fYaw, float fPitch)
{
	vForward = vLookDir * (movespeed * dt);
	vSide = vForward ^ vUp;
	vUp = { 0.0f, 1.0f, 0.0f };
	vTarget = { 0.0f, 0.0f, 1.0f };
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	vTarget = vCamera + vLookDir;
	matCamera.MatrixPointAt(vCamera, vTarget, vUp);
	matView.MatrixQuickInverse(matCamera);
}