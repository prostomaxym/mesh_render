#include <cmath>
#include <Windows.h>

#include <glut.h>

#include "main.h"
#include "graphics/Matrix.h"
#include "graphics/Mesh.h"
#include "graphics/Vector.h"
#include "utility/Keyboard.h"
#include "utility/Mouse.h"
#include "utility/Text.h"
#include "utility/Window.h"

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
float fYaw, fXaw;

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

mat4x4 matProj, matRotX, matRotY, matRotZ, matWorld, matTrans, matCamera, matView, matCameraRot;
vec3f vCamera, vForward, vSide, vLookDir;
vec3f vTarget = { 0.0f, 0.0f, 0.1f };
vec3f light_direction = { 0.0f, 1.0f, -3.0f };
vec3f vUp = { 0.0f, 1.0f, 0.0f };


int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	axis.loadFromObjectFile("objects/axis.obj");
	teapot.loadFromObjectFile("objects/teapot.obj");
	mountains.loadFromObjectFile("objects/mountains.obj");

	matProj.makeProjection(0.1f, 1000.0f, 90.0f);

	//GLut func initialization
	glutDisplayFunc(render);
	glutTimerFunc(loopdelay, gameloop, 0);
	glutKeyboardFunc(PressKeyHandler);
	glutKeyboardUpFunc(ReleaseKeyHandler);
	glutPassiveMotionFunc(PassiveMotionMouseHandler);
	glutSetCursor(GLUT_CURSOR_NONE);

	old_t = glutGet(GLUT_ELAPSED_TIME);

	//Game loop
	glutMainLoop();
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
	mountains.drawMesh(0.4f, 0.7f, 0.3f, matWorld, matView, matProj, vCamera, light_direction);
	//teapot.drawMesh(0.83f, 0.68f, 0.2f);
	
	ui.drawFpsCounter(50, 50, fps);
	glFlush();
}

void update()
{
	float fTheta = 1.0f * t / 1000;

	matRotX.rotateX(fTheta * 0.0f);
	matRotY.rotateY(fTheta * 0.0f);
	matRotZ.rotateZ(fTheta * 0.0f);

	//Update World Matrix
	matTrans.makeTranslation(0.0f, -50.0f, 200.0f);
	matWorld.makeIdentity();	//form World Matrix
	matWorld = matRotX * matRotZ * matRotY; //transform by rotation
	matWorld = matWorld * matTrans;  //transform by translation
	

	//Update camera
	vForward = vLookDir * 1.0f * dt;
	vSide = vForward ^ vUp;
	vUp = { 0,1,0 };
	vTarget = { 0,0,1 };
	matCameraRot.rotateY(fYaw);
	matCameraRot.rotateX(fXaw);
	vLookDir = MatrixMultiplyVector(matCameraRot, vTarget);
	vTarget = vCamera + vLookDir;
	matCamera.MatrixPointAt(vCamera, vTarget, vUp);
	matView.MatrixQuickInverse(matCamera);
}