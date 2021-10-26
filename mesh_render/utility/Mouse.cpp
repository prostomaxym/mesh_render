#include "Mouse.h"

#include "../main.h"

#include <glut.h>

struct MousePos
{
	int xPrevious = 0;
	int yPrevious = 0;
	int xCurrent = 0;
	int yCurrent = 0;
} mousePos;

void PassiveMotionMouseHandler(int x, int y)
{
	if (mousePos.xPrevious == 0 && mousePos.yPrevious == 0)
	{
		mousePos.xPrevious = x;
		mousePos.yPrevious = y;
	}

	mousePos.xPrevious = x;
	mousePos.yPrevious = y;
	int dx = mousePos.xCurrent - mousePos.xPrevious;
	int dy = mousePos.yCurrent - mousePos.yPrevious;
	mousePos.xPrevious = mousePos.xCurrent;
	mousePos.yPrevious = mousePos.yCurrent;

	fYaw += dx * dt / 100000.0f;
	fXaw -= dy * dt / 100000.0f;

	//glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}