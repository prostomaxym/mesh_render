#include "window.h"

#include <glut.h>

Window::Window()
{
	width_ = 1280;
	height_ = 720;
	window_name_ = "Mesh render";
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutInitWindowSize(width_, height_);
	glutCreateWindow(this->window_name_.c_str());
}

Window::Window(int w, int h, std::string winname)
{
	width_ = w;
	height_ = h;
	window_name_ = winname;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutInitWindowSize(width_, height_);
	glutCreateWindow(window_name_.c_str());
}

void Window::leaveFullscreen(int w, int h)
{
	width_ = w;
	height_ = h;
	glutReshapeWindow(w, h);
	glutPositionWindow(50, 50);
	glLoadIdentity();
}

void Window::enterFullscreen(int w, int h)
{
	width_ = w;
	height_ = h;
	glutReshapeWindow(w, h);
	glutPositionWindow(0, 0);
	glLoadIdentity();
}