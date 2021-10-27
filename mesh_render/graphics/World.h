#ifndef MESH_RENDER_GRAPHICS_WORLD_H_
#define MESH_RENDER_GRAPHICS_WORLD_H_

#include "Matrix.h"

struct World
{
	mat4x4 matProj;
	mat4x4 matRotX;
	mat4x4 matRotY;
	mat4x4 matRotZ;
	mat4x4 matWorld;
	mat4x4 matTrans;

	void makeProjection(float fNear, float fFar, float fFov);
	void makeRotation(float fXang, float fYang, float fZang);
	void makeTranslation(float x, float y, float z);
	void makeIdentity();
	void update();
};
#endif  // MESH_RENDER_GRAPHICS_WORLD_H_