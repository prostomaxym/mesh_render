#ifndef MESH_RENDER_UTILITY_MOUSE_H_
#define MESH_RENDER_UTILITY_MOUSE_H_

#include "../graphics/Camera.h"

class Mouse
{
public:
	Mouse();
	Mouse(float sens);

	void setSensitivity(float sens);
	float getSensitivity();
	void passiveMotionMouseHandler(int x, int y, Camera& cam);

private:
	int xPrevious_;
	int yPrevious_;
	int xCurrent_;
	int yCurrent_;
	int dx_;
	int dy_;
	float fSensitivity_;
};
#endif  // MESH_RENDER_UTILITY_MOUSE_H_
