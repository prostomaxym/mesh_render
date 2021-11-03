#include "Model.h"

Model::Model()
{
	modelMesh_ = Mesh();
	modelTexture_ = Texture();
}

Model::Model(std::string objFilename, std::string texFilename)
{
	modelMesh_.load(objFilename);
	modelTexture_.load(texFilename);
}

Model::~Model()
{
	modelMesh_.clear();
	modelTexture_.clear();
}

void Model::load(std::string objFilename, std::string texFilename)
{
	modelMesh_.load(objFilename);
	modelTexture_.load(texFilename);
}

void Model::clear()
{
	modelMesh_.clear();
	modelTexture_.clear();
}

void Model::draw()
{
	if (this != NULL)
	{
		modelTexture_.use();
		modelMesh_.draw();
	}
}
