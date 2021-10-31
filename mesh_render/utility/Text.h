#ifndef MESH_RENDER_UTILITY_TEXT_H_
#define MESH_RENDER_UTILITY_TEXT_H_

#include <string>

class Text
{
public:
	//Bind to left top corner
	static void drawText(int x, int y, std::string text, int number, float r = 0.0f, float g = 0.0f, float b = 0.0f);  

private:
	static void rasterText(float x, float y, int* font, std::string text);
};
#endif  // MESH_RENDER_UTILITY_TEXT_H_