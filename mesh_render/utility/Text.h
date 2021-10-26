#ifndef MESH_RENDER_UTILITY_TEXT_H_
#define MESH_RENDER_UTILITY_TEXT_H_

#include <string>

class Text
{
public:
	void drawFpsCounter(int x, int y, int fps); //Bind to left top corner

private:
	void glWrite(float x, float y, int* font, std::string text);
};
#endif  // MESH_RENDER_UTILITY_TEXT_H_