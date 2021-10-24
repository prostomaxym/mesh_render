#ifndef MESH_RENDER_MESH_H_
#define MESH_RENDER_MESH_H_

#include <string>
#include <vector>

struct vec3f
{
	float x, y, z;
	void set(float first, float second, float third);
};

struct triangle
{
	vec3f p[3];
	float dp = 1; //triangle similarity to lighting normal
};

struct mesh
{
	std::vector <triangle> tris;

	mesh();
	mesh(std::vector <triangle> input);

	void drawMesh(float r, float g, float b);
	bool loadFromObjectFile(std::string sFilename);
};

struct mat4x4
{
	float m[4][4] = {0};
};

extern mat4x4 matProj, matRotZ, matRotX;
extern vec3f vCamera;
extern vec3f light_direction;

void MultiplyMatrixVector(vec3f& i, vec3f& o, mat4x4& m);
void initProjectionMatrix(float zNear, float zFar, float Fov);

#endif  // MESH_RENDER_MESH_H_