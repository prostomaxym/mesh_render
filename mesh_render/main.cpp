#include <cmath>
#include <Windows.h>

#include <glut.h>

#include "Keyboard.h"
#include "main.h"
#include "Matrix.h"
#include "Mesh.h"
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

int loopdelay = 1;  //delay between frames in ms
int current_ticks, delta_ticks;
int fps = 0;  //fps counter

Window window(kWidth, kHeight, "Mesh Render");
Text ui;

mesh meshCube({

	// FRONT
	{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	// RIGHT                                                      
	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

	// BACK                                                     
	{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

	// LEFT                                                      
	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

	// TOP                                                       
	{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

	// BOTTOM                                                    
	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	});
mesh ship;


int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	ship.loadFromObjectFile("spaceship.obj");
	matProj.makeProjection(0.1f, 1000.0f, 90.0f);
	
	matTrans.makeTranslation(0.0f, 0.0f, 5.0f);

	matWorld.makeIdentity();	// form World Matrix
	matWorld = matRotZ * matRotX;  // transform by rotation
	matWorld = matWorld * matTrans;  // transform by translation

	//GLut func initialization
	glutDisplayFunc(render);
	glutTimerFunc(loopdelay, gameloop, 0);
	glutKeyboardUpFunc(ReleaseKeyHandler);

	//Game loop
	glutMainLoop();
	return 0;
}

void gameloop(int = 0)
{
	current_ticks = glutGet(GLUT_ELAPSED_TIME);
	
	update();
	render();

	delta_ticks = glutGet(GLUT_ELAPSED_TIME) - current_ticks; //the time, in ms, that took to render the scene
	if (delta_ticks > 0)	fps = 1000 / delta_ticks;

	glutTimerFunc(loopdelay, gameloop, 0);
}

void render()
{
	glClearColor(0.0f, 0.65f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ui.drawFpsCounter(50, 50, fps);
	//meshCube.drawMesh(0.4f, 0.7f, 0.3f);
	ship.drawMesh(0.4f, 0.7f, 0.3f);

	glFlush();
}

void update()
{
	float fElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	float fTheta = 1.0f * fElapsedTime / 1000;

	matRotX.rotateX(fTheta * 0.0f);
	matRotX.rotateY(fTheta * 1.0f);
	matRotZ.rotateZ(fTheta * 1.0f);

	matTrans.makeTranslation(0.0f, 0.0f, 8.0f);

	matWorld.makeIdentity();	// form World Matrix
	matWorld = matRotZ * matRotX;  // transform by rotation
	matWorld = matWorld * matTrans;  // transform by translation
}