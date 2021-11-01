#ifndef MESH_RENDER_GRAPHICS_MESH_H_
#define MESH_RENDER_GRAPHICS_MESH_H_

#include <string>
#include <vector>

#include "../glatter/glatter.h"

class Mesh
{
public:
	static const int NUM_VBOS = 3;

	Mesh();
	Mesh(std::string fname);
	~Mesh();

	void load(std::string fname);
	void clear();
	void draw();

private:

	GLuint VAO;
	GLuint VBO[NUM_VBOS];

	std::vector<float> verts;
	std::vector<float> uvs;
	std::vector<float> normals;

	void addFace(const std::vector<float>& vert_palette, const std::vector<float>& uv_palette,
		uint32_t a, uint32_t at, uint32_t b, uint32_t bt, uint32_t c, uint32_t ct, bool is3DTex);
};

#endif  // MESH_RENDER_GRAPHICS_MESH_H_

