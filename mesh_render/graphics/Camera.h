#ifndef RENDER_MESH_GRAPHICS_CAMERA_H_
#define RENDER_MESH_GRAPHICS_CAMERA_H_

#include "Vector.h"

class Camera
{
public:
	Camera(); //cam pos 0,0,0 | cam dir 0,0,0 | cam speed=1
	Camera(float movespd); //cam pos 0,0,0 | cam dir 0,0,0 | cam speed-set
	Camera(vec3f cameraPos, float pitchDeg, float yawDeg, float camspd); //cam pos-set | cam dir-set | cam speed - set

	void update();  //update camera position and direction
	void setAngle( float yaw, float pitch);  //set camera direction
	void lookAt();  //update lookAt matrix
	vec3f getCameraPos();

	//Camera movement
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();

private:
	float fYaw_;  //ZX plane angle between forward vec and z axis
	float fPitch_;  //YZ plane angle between forward vec and z axis
	float camspeed_;

	vec3f vCamera_;
	vec3f vUp_;
	vec3f vRight_;
	vec3f vLookDir_;
	vec3f vTarget_;
};
#endif  // RENDER_MESH_GRAPHICS_CAMERA_H_
