#include <cmath>
#include <Windows.h>

#include <glut.h>

#include "main.h"
#include "graphics/Matrix.h"
#include "graphics/Mesh.h"
#include "graphics/Vector.h"
#include "graphics/World.h"
#include "utility/Keyboard.h"
#include "utility/Mouse.h"
#include "utility/Text.h"
#include "utility/Window.h"

//Force higher performance GPU usage
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 1;
	_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

//Resolution related variables
//96 DPI - Windows constant
float DPIscale = (float)GetDpiFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) / 96;
const int kFullWidth = glutGet(GLUT_SCREEN_WIDTH) * DPIscale;  //fullscreen width resolution
const int kFullHeight = glutGet(GLUT_SCREEN_HEIGHT) * DPIscale;  //fullscreen height resolution
const int kWidth = 1280, kHeight = 720;  //default window resolution
bool fullscreen = false;  //default screen mode

int loopdelay = 1;  //delay between frames in ms
int t, old_t, dt;
int fps = 0;  //fps counter

float fYaw, fPitch;
float movespeed = 0.1f;

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
mesh axis;
mesh mountains;
mesh teapot;

World world;
mat4x4 matCamera, matView, matCameraRot;
vec3f vCamera, vForward, vSide, vLookDir;
vec3f vTarget = { 0.0f, 0.0f, 1.0f };
vec3f light_direction = { 0.0f, 1.0f, -3.0f };
vec3f vUp = { 0.0f, 1.0f, 0.0f };

int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	axis.loadFromObjectFile("objects/axis.obj");
	teapot.loadFromObjectFile("objects/teapot.obj");
	mountains.loadFromObjectFile("objects/mountains.obj");

	//World setup
	world.makeProjection(0.1f, 1000.0f, 90.0f);
	world.makeIdentity();
	world.makeRotation(0.0f, 0.0f, 0.0f);
	world.makeTranslation(0.0f, -2.0f, 8.0f);
	world.update();

	//GLut func initialization
	glutDisplayFunc(render);
	glutTimerFunc(loopdelay, gameloop, 0);
	glutKeyboardFunc(PressKeyHandler);
	glutKeyboardUpFunc(ReleaseKeyHandler);
	glutPassiveMotionFunc(PassiveMotionMouseHandler);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	old_t = glutGet(GLUT_ELAPSED_TIME);

	glutMainLoop();
	//Game loop
	return 0;
}

void gameloop(int = 0)
{
	update();
	render();

	t = glutGet(GLUT_ELAPSED_TIME);
	dt = (t - old_t);
	old_t = t;

	if (dt > 0)	fps = 1000 / dt;

	glutTimerFunc(loopdelay, gameloop, 0);
}

void render()
{
	glClearColor(0.0f, 0.65f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//axis.drawMesh(0.4f, 0.7f, 0.3f, matWorld, matView, matProj, vCamera, light_direction);
	//meshCube.drawMesh(0.4f, 0.7f, 0.3f);
	mountains.drawMesh(0.4f, 0.7f, 0.3f, world, matView, vCamera, light_direction);
	//teapot.drawMesh(0.83f, 0.68f, 0.2f, matWorld, matView, matProj, vCamera, light_direction);
	
	ui.drawFpsCounter(50, 50, fps);
	glFlush();
}

void update()
{
	//Update World Matrix
	
}

void updateCamera(float fYaw, float fPitch)
{
	vForward = vLookDir * movespeed * dt;
	vSide = vForward ^ vUp;
	vUp = { 0.0f, 1.0f, 0.0f };
	vTarget = { 0.0f, 0.0f, 1.0f };
	vLookDir = { cosf(fPitch) * cosf(fYaw), sinf(fPitch) , cosf(fPitch) * sinf(fYaw) };
	vTarget = vCamera + vLookDir;
	matCamera.MatrixPointAt(vCamera, vTarget, vUp);
	matView.MatrixQuickInverse(matCamera);
}
