#include "Keyboard.h"

#include "main.h"

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