#version 460 core

in vec3 in_pos;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(in_pos, 1.0);
}