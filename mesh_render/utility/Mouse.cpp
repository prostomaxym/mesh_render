#include "Mouse.h"

#include <glut.h>

Mouse::Mouse()
{
	xPrevious_ = 0;
	yPrevious_ = 0;
	xCurrent_ = 0;
	yCurrent_ = 0;
	dx_ = 0;
	dy_ = 0;
	fSensitivity_ = 1.0f;
}

Mouse::Mouse(float sens)
{
	xPrevious_ = 0;
	yPrevious_ = 0;
	xCurrent_ = 0;
	yCurrent_ = 0;
	dx_ = 0;
	dy_ = 0;
	fSensitivity_ = sens;
}

void Mouse::setSensitivity(float sens)
{
	fSensitivity_ = sens;
}

float Mouse::getSensitivity()
{
	return fSensitivity_;
}

void Mouse::passiveMotionMouseHandler(int x, int y, Camera& cam)
{
	if (xPrevious_ == 0 && yPrevious_ == 0)
	{
		xPrevious_ = x;
		yPrevious_ = y;
	}

	xCurrent_ = x;
	yCurrent_ = y;

	dx_ = xCurrent_ - xPrevious_;
	dy_ = yCurrent_ - yPrevious_;

	xPrevious_ = xCurrent_;
	yPrevious_ = yCurrent_;

	cam.setAngle(fSensitivity_ * dx_ / 1000.0f,
							 fSensitivity_ * dy_ / 1000.0f);
	//cam.update();
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	xPrevious_ = glutGet(GLUT_WINDOW_WIDTH) / 2;
	yPrevious_ = glutGet(GLUT_WINDOW_HEIGHT) / 2;
}