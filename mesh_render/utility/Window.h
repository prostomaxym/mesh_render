#ifndef MESH_RENDER_UTILITY_WINDOW_H_
#define MESH_RENDER_UTILITY_WINDOW_H_

#include <string>

class Window
{
public:
	Window();
	Window(int w, int h, std::string winname);

	void enterFullscreen(int w, int h);
	void leaveFullscreen(int w, int h);

private:
	int width_, height_; //window resolution
	std::string window_name_;
};
#endif  // MESH_RENDER_UTILITY_WINDOW_H_

