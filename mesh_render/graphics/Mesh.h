#ifndef MESH_RENDER_MESH_H_
#define MESH_RENDER_MESH_H_

#include <string>
#include <vector>

#include "Matrix.h"
#include "Vector.h"

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
#endif  // MESH_RENDER_MESH_H_