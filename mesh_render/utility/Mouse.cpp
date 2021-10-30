#include "Mouse.h"

#include <glut.h>

Mouse::Mouse()
{
	this->xPrevious = 0;
	this->yPrevious = 0;
	this->xCurrent = 0;
	this->yCurrent = 0;
	this->dx = 0;
	this->dy = 0;
	this->fSensitivity = 1.0f;
}

Mouse::Mouse(float sens)
{
	this->xPrevious = 0;
	this->yPrevious = 0;
	this->xCurrent = 0;
	this->yCurrent = 0;
	this->dx = 0;
	this->dy = 0;
	this->fSensitivity = sens;
}

void Mouse::setSensitivity(float sens)
{
	this->fSensitivity = sens;
}

float Mouse::getSensitivity()
{
	return this->fSensitivity;
}

void Mouse::passiveMotionMouseHandler(int x, int y, Camera& cam)
{
	if (this->xPrevious == 0 && this->yPrevious == 0)
	{
		this->xPrevious = x;
		this->yPrevious = y;
	}

	this->xCurrent = x;
	this->yCurrent = y;

	this->dx = this->xCurrent - this->xPrevious;
	this->dy = this->yCurrent - this->yPrevious;

	this->xPrevious = this->xCurrent;
	this->yPrevious = this->yCurrent;

	cam.setAngle(this->fSensitivity * this->dx / 1000.0f,
							 this->fSensitivity * this->dy / 1000.0f);
	cam.update();
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	this->xPrevious = glutGet(GLUT_WINDOW_WIDTH) / 2;
	this->yPrevious = glutGet(GLUT_WINDOW_HEIGHT) / 2;
}