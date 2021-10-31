#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h> 
#include "glatter/glatter.h"  //load glext function pointers

#include "main.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "utility/Keyboard.h"
#include "utility/Mouse.h"
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
Window window(kWidth, kHeight, "Mesh Render");

const int maxfps = 250;  //max fps lock
int frametime_lock = 1000 / maxfps;  //min frametime lock
int t, old_t, dt;  //elapsed time, deltatime between frames
int fps = 0;  //fps counter
float POV = 85.0f, zNear = 0.1f, zFar = 10000.0f;  //Perspective params

unsigned int texture;

Camera camera(/*camera speed=*/1.0f);
Mouse mouse(/*mouse sensitivity =*/1.0f);
Keyboard keyboard;

mesh level;
mesh level2;
mesh level3;

//TODO:
// key binding
// refactor texture loading
// enhance mesh class
// make object class

int main()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);

	initGL(POV, zNear, zFar);
	initGLUT();

	//level.loadFromObjectFile("levels/Hurricos/Hurricos2.obj", true);
	//LoadTextures("levels/Hurricos/s2-1_024-n.T.png");

	level2.loadFromObjectFile("levels/Autumn Plains/Autumn Plains.obj", true);
	LoadTextures("levels/Autumn Plains/spyro_autumn_plains.png");

	//level3.loadFromObjectFile("levels/Summer Forest/Summer Forest.obj", true);
	//LoadTextures("levels/Summer Forest/s2-1_016-n.png");


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

	//level.drawMesh(0.4f, 1.0f, 0.3f);
	level2.drawMesh(0.4f, 1.0f, 0.3f);
	//level3.drawMesh(0.4f, 1.0f, 0.3f);

	glFlush();
}

void update()
{
	keyboard.update(camera);
}

void LoadTextures(std::string filename)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
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