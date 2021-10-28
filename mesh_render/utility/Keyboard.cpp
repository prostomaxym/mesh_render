#include "Keyboard.h"

#include "../main.h"

#include <glut.h>

void PressKeyHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		camera.vCamera = camera.vCamera + camera.vSide;
		break;
	case 'd':
		camera.vCamera = camera.vCamera - camera.vSide;
		break;
	case 'w':
		camera.vCamera = camera.vCamera + camera.vForward;
		break;
	case 's':
		camera.vCamera = camera.vCamera - camera.vForward;
		break;
	case 32: 
		camera.vCamera = camera.vCamera + camera.vUp;
		break;
	case 'c':
		camera.vCamera = camera.vCamera - camera.vUp;
		break;
	case 'q':
		camera.fYaw += 0.1f;
		break;
	case 'e':
		camera.fYaw -= 0.1f;
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
