#ifndef MESH_RENDER_GRAPHICS_MODEL_H_
#define MESH_RENDER_GRAPHICS_MODEL_H_

#include <string>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();
	Model(std::string objFilename, std::string texFilename);
	~Model();

	void load(std::string objFilename, std::string texFilename);
	void clear();

	void draw();

private:
	Mesh modelMesh_;
	Texture modelTexture_;
};
#endif  // MESH_RENDER_GRAPHICS_MODEL_H_
