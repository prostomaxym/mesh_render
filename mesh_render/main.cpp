#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h> 
#include "glatter/glatter.h"  //load glext function pointers

#include "main.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "graphics/Matrix.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
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
Window window(kWidth, kHeight, "Mesh Render");

const float maxfps = 250;  //max fps lock
int frametime_lock = 1000 / maxfps;  //min frametime lock
int t, old_t, dt;  //elapsed time, deltatime between frames
int fps = 0;  //fps counter
float POV = 85.0f, zNear = 0.1f, zFar = 10000.0f;  //Perspective params

Camera camera(/*camera speed=*/1.0f);
Mouse mouse(/*mouse sensitivity =*/1.0f);
Keyboard keyboard;

WorldMatrix matWorld;
Light sun(/*light position=*/	{4000.0f, 6000.0f, 1500.0f}, 
	/*initial camera position*/	{0.0f, 0.0f, 0.0f}, 
	/*light color*/							{0.95f, 0.85f, 0.65f});
Mesh lev1("levels/Hurricos/Hurricos2.obj");
Mesh lev2("levels/Autumn Plains/Autumn Plains2.obj");
Mesh lev3("levels/Summer Forest/Summer Forest.obj");
//Mesh lev4("levels/Anor Londo.obj");
//Texture* t4;
Texture* t1, * t2, * t3;
//Shader texShader("shaders/texture.vert", "shaders/texture.frag");
Shader texShader("shaders/blinnphong.vert", "shaders/blinnphong.frag");

//TODO:
// make object class

int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	//initialise GL and GLUT
	initGL(POV, zNear, zFar);
	initGLUT();

	//Select active shader
	texShader.use();
	matWorld.init(texShader);
	sun.initLight(texShader, camera);

	//Load textures
	t1 = new Texture("levels/Hurricos/s2-1_024-n.T.png");
	t2 = new Texture("levels/Autumn Plains/spyro_autumn_plains.png");
	t3 = new Texture("levels/Summer Forest/s2-1_016-n.png");
	//t4 = new Texture("levels/texture2.png");

	t2->use();
	
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
	matWorld.update(texShader);
	sun.updateLight(texShader, camera);

	lev2.draw();

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
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
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





