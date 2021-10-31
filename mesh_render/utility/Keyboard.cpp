#include "Keyboard.h"

#include <algorithm>

#include <glut.h>
#include "../main.h"

Keyboard::Keyboard() : 
	lastState { false },
	currentState { false }
{
	keyBinding["moveLeft"] = 'a';
	keyBinding["moveRight"] = 'd';
	keyBinding["moveForward"] = 'w';
	keyBinding["moveBackward"] = 's';

	keyBinding["moveUp"] = 32;
	keyBinding["moveDown"] = 'c';

	keyBinding["toggleZoom"] = 'g';
	keyBinding["toggleFullscreen"] = 'f';
}

void Keyboard::setKeyState(unsigned char keycode, bool state)
{
	currentState[keycode] = state;
}

void Keyboard::update(Camera& cam)
{
	processInput(cam);
	cam.update();
	std::copy(std::begin(currentState), std::end(currentState), std::begin(lastState));
}

void Keyboard::processInput(Camera& cam)
{
	if (isHeld('a'))	cam.moveLeft();
	else if (isHeld('d'))		cam.moveRight();

	if (isHeld('w'))		cam.moveForward();
	else if (isHeld('s'))		cam.moveBackward();

	if (isHeld(32))		cam.moveUp();
	else if (isHeld('c'))		cam.moveDown();

	if (isHeld('g'))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(POV / 2, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
	}
	else if (isReleased('g'))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(POV, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
	}

	if (isPressed('f'))
	{
		if (fullscreen)
		{
			window.leaveFullscreen(kWidth, kHeight);
			fullscreen = false;
		}
		else
		{
			window.enterFullscreen(kFullWidth, kFullHeight);
			fullscreen = true;
		}
	}
}

bool Keyboard::isHeld(unsigned char keycode)
{
	if (lastState[keycode] == true && currentState[keycode] == true)
		return true;
	else 
		return false;
}
bool Keyboard::isPressed(unsigned char keycode)
{
	if (lastState[keycode] == false && currentState[keycode] == true)
		return true;
	else
		return false;
}

bool Keyboard::isReleased(unsigned char keycode)
{
	if (lastState[keycode] == true && currentState[keycode] == false)
		return true;
	else
		return false;
}