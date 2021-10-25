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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width, 0, this->height);
}

Window::Window(int w, int h, std::string winname)
{
	this->width = w;
	this->height = h;
	this->window_name = winname;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow(this->window_name.c_str());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width, 0, this->height);
}

void Window::leaveFullscreen(int w, int h)
{
	glutReshapeWindow(w, h);
	glutPositionWindow(50, 50);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}

void Window::enterFullscreen(int w, int h)
{
	glutReshapeWindow(w, h);
	glutPositionWindow(0, 0);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}