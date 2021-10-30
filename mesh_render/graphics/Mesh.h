#ifndef MESH_RENDER_GRAPHICS_MESH_H_
#define MESH_RENDER_GRAPHICS_MESH_H_

#include <string>
#include <vector>

#include "Camera.h"
#include "Vector.h"

struct triangle
{
	vec3f p[3];
	vec2f t[3];
};

struct mesh
{
	std::vector <triangle> tris;

	mesh();
	mesh(std::vector <triangle> polygons);

	void drawMesh(float r, float g, float b);
	bool loadFromObjectFile(std::string sFilename, bool bHasTexture = false);
};
#endif  // MESH_RENDER_GRAPHICS_MESH_H_