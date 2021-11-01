#ifndef MESH_RENDER_GRAPHICS_SHADER_H_
#define MESH_RENDER_GRAPHICS_SHADER_H_

#include <string>
#include <vector>

#include "../glatter/glatter.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	unsigned int getID();

private:
	unsigned int ID;

	void checkCompileErrors(unsigned int shader, std::string type);
};
#endif  // MESH_RENDER_GRAPHICS_SHADER_H_
