#ifndef RENDER_MESH_GRAPHICS_CAMERA_H_
#define RENDER_MESH_GRAPHICS_CAMERA_H_

#include "Matrix.h"
#include "Vector.h"

struct Camera
{
	float fYaw;
	float fPitch;
	float movespeed = 0.1f;
	mat4x4 matCamera;
	mat4x4 matView;
	mat4x4 matCameraRot;
	vec3f vCamera, vForward, vSide, vLookDir;
	vec3f vTarget = { 0.0f, 0.0f, 1.0f };
	vec3f vUp = { 0.0f, 1.0f, 0.0f };

	void update(float fYaw, float fPitch);
};
#endif  // RENDER_MESH_GRAPHICS_CAMERA_H_
