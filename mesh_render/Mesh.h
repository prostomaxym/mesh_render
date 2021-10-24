#ifndef MESH_RENDER_MESH_H_
#define MESH_RENDER_MESH_H_

#include <vector>

struct vec3f
{
	float x, y, z;
};

struct triangle
{
	vec3f p[3];
};

struct mesh
{
	std::vector <triangle> tris;
	void drawMesh(float r, float g, float b);
};

struct mat4x4
{
	float m[4][4] = {0};
};

extern mat4x4 matProj, matRotZ, matRotX;

void MultiplyMatrixVector(vec3f& i, vec3f& o, mat4x4& m);

#endif  // MESH_RENDER_MESH_H_