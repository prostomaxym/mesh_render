#ifndef RENDER_MESH_GRAPHICS_CAMERA_H_
#define RENDER_MESH_GRAPHICS_CAMERA_H_

#include "Matrix.h"
#include "Vector.h"

struct Camera
{
	float fYaw;
	float fPitch;
	float movespeed = 1.0f;

	vec3f vCamera, vForward, vSide, vLookDir;
	vec3f vTarget = { 0.0f, 0.0f, 0.0f };
	vec3f vUp = { 0.0f, 1.0f, 0.0f };

	void update();
};
#endif  // RENDER_MESH_GRAPHICS_CAMERA_H_
