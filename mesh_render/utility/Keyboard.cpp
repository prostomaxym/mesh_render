#include "Keyboard.h"

#include <glut.h>
#include "../main.h"

void PressKeyHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		camera.moveLeft();
		break;
	case 'd':
		camera.moveRight();
		break;
	case 'w':
		camera.moveForward();
		break;
	case 's':
		camera.moveBackward();
		break;
	case 32: 
		camera.moveUp();
		break;
	case 'c':
		camera.moveDown();
		break;
	case 'g':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		break;
	}
	camera.update();
}

void ReleaseKeyHandler(unsigned char key, int x, int y)
{
	if (key == 'f')
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
	if (key == 'g')
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLoadIdentity();
		gluPerspective(85.0f, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
	}
}
