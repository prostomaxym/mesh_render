#include "Keyboard.h"

#include "../main.h"

#include <glut.h>

void PressKeyHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		vCamera = vCamera + vSide;
		break;
	case 'd':
		vCamera = vCamera - vSide;
		break;
	case 'w':
		vCamera = vCamera + vForward;
		break;
	case 's':
		vCamera = vCamera - vForward;
		break;
	case 32: 
		vCamera = vCamera - vUp;
		break;
	case 'c':
		vCamera = vCamera + vUp;
		break;
	}
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
