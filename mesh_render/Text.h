#ifndef MESH_RENDER_TEXT_H_
#define MESH_RENDER_TEXT_H_

#include <string>

class Text
{
public:
	void drawFpsCounter(int x, int y, int fps); //Bind to left top corner

private:
	void glWrite(float x, float y, int* font, std::string text);
};
#endif  // PATHFINDING_VISUALIZER_TEXT_H_