#include <cmath>
#include <bitset>
#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h> 
#include "libraries/glatter/glatter.h"  //load glext functions pointers

#include "main.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "graphics/Mesh.h"
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "graphics/WorldMatrix.h"
#include "utility/Keyboard.h"
#include "utility/Mouse.h"
#include "utility/Window.h"

//Force higher performance GPU usage
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 1;
	//_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

//Resolution related variables
//96 DPI - Windows constant
float DPIscale = (float)GetDpiFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) / 96;
const int kFullWidth = glutGet(GLUT_SCREEN_WIDTH) * DPIscale;  //fullscreen width resolution
const int kFullHeight = glutGet(GLUT_SCREEN_HEIGHT) * DPIscale;  //fullscreen height resolution
const int kWidth = 1280, kHeight = 720;  //default window resolution
bool fullscreen = false;  //default screen mode
Window window(kWidth, kHeight, "Mesh Render"); //window construction

const float maxfps = 500;  //max fps lock
int frametime_lock = 1000 / maxfps;  //min frametime lock
int t, old_t, dt;  //elapsed time, deltatime between frames
int fps = 0;  //fps counter
float POV = 85.0f, zNear = 0.1f, zFar = 120000.0f;  //perspective params
int demoLevel = 2;  //keyboard switch value for demo levels

Camera camera(/*camera speed=*/1.0f);
Mouse mouse(/*mouse sensitivity =*/1.0f);
Keyboard keyboard;
WorldMatrix matWorld;

//Static light setup
//final illuminance result depends on sourcePower/ distance^2
//float sourcePower = powf(10.0f, 10.0f); 
//Light sun(/*light position=*/	{ 80000.0f, 60000.0f, 15000.0f },
//					/*light power*/			0.9f * sourcePower,
//					/*light color*/			{ 0.95f, 0.85f, 0.65f },
//					/*day period(sec)*/	60.0f);

//Dynamic light setup
//final illuminance result depends on sourcePower/ distance^2
float distance = powf(10.0f, 5.0f);
float sourcePower = powf(10.0f, 10.0f); 

Light sun(/*distance*/				distance,
					/*source power*/		0.9f * sourcePower,
					/*light color*/			{ 0.95f, 0.85f, 0.65f }, 
					/*zAxis offset*/		15000.0f,
					/*day period(sec)*/	60.0f);
Mesh lightSphere("models/sun.obj");

//Models
Model* level1;
Model* level2;
Model* level3;
Model* level4;

//Shaders
//Shader texShader("shaders/phong.vert", "shaders/phong.frag");  //Phong reflection shader
Shader texShader("shaders/blinnphong.vert", "shaders/blinnphong.frag");  // Blinn-Phong reflection shader
Shader lightSphereShader("shaders/lightSphere.vert", "shaders/lightSphere.frag");

//TODO:
// cleanup


struct PrevJoystickState
{
	int x = 0;
	int y = 0;
} state;

int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	//Initialise GL and GLUT
	initGL(POV, zNear, zFar);
	initGLUT();

	//Setup scene
	texShader.use();
	matWorld.init(texShader);
	sun.initLight(texShader, camera);
	
	//Load models
	//models are read from files in a very straight forward way
	//thus loadings times can be significant
	level1 = new Model("models/Hurricos/Hurricos.obj", "models/Hurricos/s2-1_024-n.T.png");
	level2 = new Model("models/Autumn Plains/Autumn Plains.obj", "models/Autumn Plains/spyro_autumn_plains.png");
	level3 = new Model("models/Summer Forest/Summer Forest.obj", "models/Summer Forest/s2-1_016-n.png");
	//level4 = new Model("models/Anor Londo/Anor Londo.obj", "models/Anor Londo/texture.png");  
	//>100MB models are not included in github repo

	old_t = glutGet(GLUT_ELAPSED_TIME);
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

	glutTimerFunc(frametime_lock, gameloop, 0);
}

void render()
{
	glClearColor(0.0f, 0.65f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	camera.lookAt();

	texShader.use();
	matWorld.update(texShader);
	//sun.updateStaticLight(texShader, camera);
	sun.updateDynamicLight(texShader, camera, dt);

	switch (demoLevel)
	{
	case 1:
		level1->draw();
		break;
	case 2:
		level2->draw();
		break;
	case 3:
		level3->draw();
		break;
	case 4:
		//level4->draw();
		break;
	}
	
	lightSphereShader.use();
	matWorld.translate(lightSphereShader, sun.getLightPos());
	matWorld.scale(lightSphereShader, { 10.0f, 10.0f, 10.0f });
	lightSphere.draw();

	glFlush();
}

void update()
{
	keyboard.update(camera);
	camera.update();
}

void initGL(float POV, float zNear, float zFar)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(POV, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}

void initGLUT()
{
	glutDisplayFunc(render);
	glutTimerFunc(frametime_lock, gameloop, 0);
	glutKeyboardFunc(pressKeyCallback);
	glutKeyboardUpFunc(releaseKeyCallback);
	glutJoystickFunc(joystickCallback,2);
	glutIgnoreKeyRepeat(true);
	glutPassiveMotionFunc(passiveMouseMotionCallback);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void passiveMouseMotionCallback(int x, int y)
{
	mouse.passiveMotionMouseHandler(x, y, camera);
}

void pressKeyCallback(unsigned char key, int x, int y)
{
	keyboard.setKeyState(key, true);
}

void releaseKeyCallback(unsigned char key, int x, int y)
{
	keyboard.setKeyState(key, false);
}

void joystickCallback(unsigned int buttonMask, int x, int y, int z)
{
	// TODO: implement stick deadzone
	//if (std::abs(x) < 100 || std::abs(y) < 100)
	//	return;

	std::bitset<4> mask(buttonMask);
	if (mask[0])
		keyboard.setKeyState('a', true);
	else
		keyboard.setKeyState('a', false);

	if (mask[1])
		keyboard.setKeyState('s', true);
	else
		keyboard.setKeyState('s', false);

	if (mask[2])
		keyboard.setKeyState('d', true);
	else
		keyboard.setKeyState('d', false);

	if (mask[3])
		keyboard.setKeyState('w', true);
	else
		keyboard.setKeyState('w', false);

	// Manual sensetivity controll
	x /= 10;
	y /= 10;

	int deltax = state.x - x;
	int deltay = state.y - y;

	deltax = deltax * 1000 / glutGet(GLUT_WINDOW_WIDTH);
	deltay = deltay * 1000 / glutGet(GLUT_WINDOW_HEIGHT);

	int xpos = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int ypos = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	mouse.passiveMotionMouseHandler(xpos - deltax, ypos - deltay, camera);
}





