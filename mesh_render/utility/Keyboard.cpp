#include "Keyboard.h"

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
}
