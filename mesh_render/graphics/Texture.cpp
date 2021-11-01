#include "Texture.h"

#include "../stb_image.h"

Texture::Texture()
{
	texID_ = NULL;
}

Texture::Texture(std::string fname)
{
	load(fname);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texID_);
	texID_ = NULL;
}

void Texture::load(std::string fname)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fname.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		//select color format
		GLint format;
		switch (nrChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			return;
		}

		glGenTextures(1, &texID_);
		glBindTexture(GL_TEXTURE_2D, texID_);

		//set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//load and generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else texID_ = NULL;
	stbi_image_free(data);
}

void Texture::use()
{
	if (texID_ != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID_);
	}
}

void Texture::clear()
{
	glDeleteTextures(1, &texID_);
	texID_ = NULL;
}

GLuint Texture::getID()
{
	return texID_;
}
