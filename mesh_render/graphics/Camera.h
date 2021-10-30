#ifndef RENDER_MESH_GRAPHICS_CAMERA_H_
#define RENDER_MESH_GRAPHICS_CAMERA_H_

#include "Vector.h"

class Camera
{
public:
	Camera(); //cam pos 0,0,0 | cam dir 0,0,0 | cam speed=1
	Camera(float movespd); //cam pos 0,0,0 | cam dir 0,0,0 | cam speed-set
	Camera(vec3f cameraPos, float pitch, float yaw, float camspd); //cam pos-set | cam dir-set | cam speed - set

	void update();  //update camera position and direction
	void setAngle( float yaw, float pitch);  //update camera direction
	void lookAt();  //update lookAt matrix

	//Camera movement
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();

private:
	float fYaw;  //ZX plane angle between forward vec and z axis
	float fPitch;  //YZ plane angle between forward vec and z axis
	float camspeed;

	vec3f vCamera;
	vec3f vForward;
	vec3f vSide;
	vec3f vLookDir;
	vec3f vTarget;
	vec3f vUp;
};
#endif  // RENDER_MESH_GRAPHICS_CAMERA_H_
