#ifndef MESH_RENDER_MAIN_H_
#define MESH_RENDER_MAIN_H_

#include <string>

#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "utility/Window.h"

//Resolution related variables
extern float DPIscale;
extern const int kFullWidth;  //fullscreen width resolution
extern const int kFullHeight;  //fullscreen height resolution
extern const int kWidth, kHeight;  //default window resolution
extern bool fullscreen;  //default screen mode

extern int t, old_t, dt;
extern float POV, zNear, zFar;

extern Window window;

void update();
void render();
void gameloop(int);

void initGL(float POV, float zNear, float zFar);
void initGLUT();

void passiveMouseMotionCallback(int x, int y);
void pressKeyCallback(unsigned char key, int x, int y);
void releaseKeyCallback(unsigned char key, int x, int y);
#endif  // MESH_RENDER_MAIN_H_
