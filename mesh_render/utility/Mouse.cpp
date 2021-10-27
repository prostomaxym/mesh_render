#include "Mouse.h"

#include <cmath>

#include <glut.h>

#include "../main.h"

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

	mousePos.xCurrent = x;
	mousePos.yCurrent = y;
	int dx = mousePos.xCurrent - mousePos.xPrevious;
	int dy = mousePos.yCurrent - mousePos.yPrevious;
	mousePos.xPrevious = mousePos.xCurrent;
	mousePos.yPrevious = mousePos.yCurrent;

	camera.fYaw += fmod(dx / 1000.0f, 6.28f);
	camera.fPitch -= 1.0f * dy / 1000.0f;

	if (camera.fPitch > 1.57f)
	{
		camera.fPitch = 1.57f - 0.0001f;
	}
	else if (camera.fPitch < -1.57f)
	{
		camera.fPitch = -1.57f + 0.0001f;
	}

	camera.update(-1.0f*camera.fYaw, camera.fPitch);

	if (x <= glutGet(GLUT_WINDOW_WIDTH) - 300 || y <= glutGet(GLUT_WINDOW_HEIGHT) - 300
		||x >= glutGet(GLUT_WINDOW_WIDTH) + 300 || y >= glutGet(GLUT_WINDOW_HEIGHT) + 300)
	{
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		mousePos.xPrevious = glutGet(GLUT_WINDOW_WIDTH) / 2;
		mousePos.yPrevious = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	}
}