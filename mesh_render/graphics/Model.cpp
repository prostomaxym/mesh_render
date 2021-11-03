#include "Model.h"

Model::Model()
{
	modelMesh_ = Mesh();
	modelTexture_ = Texture();
}

Model::Model(std::string objPath, std::string texPath)
{
	modelMesh_.load(objPath);
	modelTexture_.load(texPath);
}

Model::~Model()
{
	modelMesh_.clear();
	modelTexture_.clear();
}

void Model::load(std::string objPath, std::string texPath)
{
	modelMesh_.load(objPath);
	modelTexture_.load(texPath);
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
