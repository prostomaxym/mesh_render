#include <Windows.h>

#include <chrono>

#include <glut.h>

#include "Keyboard.h"
#include "main.h"
#include "Text.h"
#include "Window.h"

void update();
void render();
void gameloop(int);

//Resolution related variables
//96 DPI - Windows constant
float DPIscale = (float)GetDpiFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) / 96;
const int kFullWidth = glutGet(GLUT_SCREEN_WIDTH) * DPIscale;  //fullscreen width resolution
const int kFullHeight = glutGet(GLUT_SCREEN_HEIGHT) * DPIscale;  //fullscreen height resolution
const int kWidth = 1280, kHeight = 720;  //default window resolution
bool fullscreen = false;  //default screen mode
int loopdelay = 0;  //delay between frames
clock_t current_ticks, delta_ticks;
clock_t fps = 0;

Window window(kWidth, kHeight, "Mesh Render");
Text ui;

int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	//GLut func initialization
	glutDisplayFunc(render);
	glutTimerFunc(0, gameloop, 0);
	glutKeyboardUpFunc(ReleaseKeyHandler);

	//Game loop
	glutMainLoop();
	return 0;
	return 0;
}

void gameloop(int = 0)
{
	current_ticks = clock();
	
	update();
	render();

	delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
	if (delta_ticks > 0)	fps = CLOCKS_PER_SEC / delta_ticks;
	glutTimerFunc(0, gameloop, 0);
}

void render()
{
	glClearColor(0.0f, 0.65f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ui.drawFpsCounter(50, 50, fps);

	glFlush();
}

void update()
{

}