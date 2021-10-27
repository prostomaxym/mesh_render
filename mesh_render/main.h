#ifndef MESH_RENDER_MAIN_H_
#define MESH_RENDER_MAIN_H_

#include "graphics/Vector.h"
#include "utility/Window.h"

//Resolution related variables
extern float DPIscale;
extern const int kFullWidth;  //fullscreen width resolution
extern const int kFullHeight;  //fullscreen height resolution
extern const int kWidth, kHeight;  //default window resolution
extern bool fullscreen;  //default screen mode

extern int t, old_t, dt;
extern float fYaw, fPitch;

extern Window window;

extern vec3f vCamera, vForward, vSide, vUp;

void update();
void render();
void gameloop(int);
void updateCamera(float fY, float fX);
#endif  // MESH_RENDER_MAIN_H_
