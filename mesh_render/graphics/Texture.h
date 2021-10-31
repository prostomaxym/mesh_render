#ifndef MESH_RENDER_GRAPHICS_TEXTURE_H_
#define MESH_RENDER_GRAPHICS_TEXTURE_H_

#include <string>

#include "../glatter/glatter.h"

class Texture
{
public:
	Texture();
	Texture(std::string fname);
	~Texture();

	void load(std::string fname);
	void use();
	void clear();

private:
	GLuint texID_;
};
#endif  // MESH_RENDER_GRAPHICS_TEXTURE_H_
