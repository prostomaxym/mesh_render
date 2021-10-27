#ifndef MESH_RENDER_MAIN_H_
#define MESH_RENDER_MAIN_H_

#include "graphics/Camera.h"
#include "graphics/Vector.h"
#include "utility/Window.h"

//Resolution related variables
extern float DPIscale;
extern const int kFullWidth;  //fullscreen width resolution
extern const int kFullHeight;  //fullscreen height resolution
extern const int kWidth, kHeight;  //default window resolution
extern bool fullscreen;  //default screen mode

extern int t, old_t, dt;
extern bool allowPolygonLines;

extern Window window;
extern Camera camera;

void update();
void render();
void gameloop(int);
#endif  // MESH_RENDER_MAIN_H_
