#ifndef MESH_RENDER_UTILITY_KEYBOARD_H_
#define MESH_RENDER_UTILITY_KEYBOARD_H_

#include "../graphics/Camera.h"

class Keyboard
{
public:
	Keyboard();

	void setKeyState(unsigned char keycode, bool state);
	void update(Camera& cam);
	
private:
	bool lastState[256];  //true - key down; false - up
	bool currentState[256];  //true - key down; false - up

	void processInput(Camera& cam);
	bool isHeld(unsigned char keycode);
	bool isPressed(unsigned char keycode);
	bool isReleased(unsigned char keycode);
};
#endif  // MESH_RENDER_UTILITY_KEYBOARD_H_
