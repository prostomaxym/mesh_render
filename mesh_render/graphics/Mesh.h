#ifndef MESH_RENDER_GRAPHICS_MESH_H_
#define MESH_RENDER_GRAPHICS_MESH_H_

#include <string>
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "World.h"

struct triangle
{
	vec3f p[3];
	float dp = 1; //triangle similarity to lighting normal
};

struct mesh
{
	std::vector <triangle> tris;

	mesh();
	mesh(std::vector <triangle> polygons);

	void drawMesh(float r, float g, float b, 
		World& world,
		mat4x4& matView,
		vec3f& vCamera,
		vec3f& light_direction);
	bool loadFromObjectFile(std::string sFilename);
};

int TriangleClipAgainstPlane(vec3f plane_p, vec3f plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2);
#endif  // MESH_RENDER_GRAPHICS_MESH_H_