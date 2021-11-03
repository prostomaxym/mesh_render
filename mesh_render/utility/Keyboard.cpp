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

	keyBinding["moveUp"] = ' ';
	keyBinding["moveDown"] = 'c';

	keyBinding["toggleZoom"] = 'g';
	keyBinding["toggleFullscreen"] = 'f';

	keyBinding["selectLevel1"] = '1';
	keyBinding["selectLevel2"] = '2';
	keyBinding["selectLevel3"] = '3';
	keyBinding["selectLevel4"] = '4';
}

void Keyboard::setKeyState(unsigned char keycode, bool state)
{
	currentState[keycode] = state;
}

void Keyboard::update(Camera& cam)
{
	processInput(cam);
	for (auto& n : keyBinding)
	{
		lastState[n.second] = currentState[n.second];
	}
}

void Keyboard::processInput(Camera& cam)
{
	if (isHeld(keyBinding["moveLeft"]))		cam.moveLeft();
	else if (isHeld(keyBinding["moveRight"]))		cam.moveRight();

	if (isHeld(keyBinding["moveForward"]))		cam.moveForward();
	else if (isHeld(keyBinding["moveBackward"]))		cam.moveBackward();

	if (isHeld(keyBinding["moveUp"]))		cam.moveUp();
	else if (isHeld(keyBinding["moveDown"]))		cam.moveDown();

	if (isHeld(keyBinding["toggleZoom"]))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(POV / 2, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
	}
	else if (isReleased(keyBinding["toggleZoom"]))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(POV, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
	}

	if (isPressed(keyBinding["toggleFullscreen"]))
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

	if (isPressed(keyBinding["selectLevel1"]))
	{
		demoLevel = 1;
	}
	else if (isPressed(keyBinding["selectLevel2"]))
	{
		demoLevel = 2;
	}
	else if (isPressed(keyBinding["selectLevel3"]))
	{
		demoLevel = 3;
	}
	else if (isPressed(keyBinding["selectLevel4"]))
	{
		demoLevel = 4;
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