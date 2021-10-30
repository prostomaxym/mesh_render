#include "window.h"

#include <glut.h>

Window::Window()
{
	this->width = 1280;
	this->height = 720;
	this->window_name = "Pathfinding algorithms visualizer";
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow(this->window_name.c_str());
}

Window::Window(int w, int h, std::string winname)
{
	this->width = w;
	this->height = h;
	this->window_name = winname;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow(this->window_name.c_str());
}

void Window::leaveFullscreen(int w, int h)
{
	this->width = w;
	this->height = h;
	glutReshapeWindow(w, h);
	glutPositionWindow(50, 50);
	glLoadIdentity();
}

void Window::enterFullscreen(int w, int h)
{
	this->width = w;
	this->height = h;
	glutReshapeWindow(w, h);
	glutPositionWindow(0, 0);
	glLoadIdentity();
}