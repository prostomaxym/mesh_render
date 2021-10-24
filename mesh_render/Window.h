#ifndef MESH_RENDER_WINDOW_H_
#define MESH_RENDER_WINDOW_H_

#include <string>

class Window
{
public:
	Window();
	Window(int w, int h, std::string winname);

	void enterFullscreen(int w, int h);
	void leaveFullscreen(int w, int h);

private:
	int width, height; //window resolution
	std::string window_name;
};
#endif  // MESH_RENDER_WINDOW_H_

