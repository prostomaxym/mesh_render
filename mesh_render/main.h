#ifndef MESH_RENDER_MAIN_H_
#define MESH_RENDER_MAIN_H_

#include "utility/Window.h"

//Resolution related variables
extern float DPIscale;
extern const int kFullWidth;  //fullscreen width resolution
extern const int kFullHeight;  //fullscreen height resolution
extern const int kWidth, kHeight;  //default window resolution
extern bool fullscreen;  //default screen mode

extern int t, old_t, dt;  //elapsed time, deltatime
extern float POV, zNear, zFar;  //perspective params
extern int demoLevel;  //keyboard switch for demo levels

extern Window window;

void update();
void render();
void gameloop(int);

void initGL(float POV, float zNear, float zFar);
void initGLUT();

void passiveMouseMotionCallback(int x, int y);
void pressKeyCallback(unsigned char key, int x, int y);
void releaseKeyCallback(unsigned char key, int x, int y);
void joystickCallback(unsigned int buttonMask, int x, int y, int z);
#endif  // MESH_RENDER_MAIN_H_
