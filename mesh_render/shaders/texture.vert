#version 460

//Inputs
in vec3 in_pos;
in vec2 in_uv;
in vec3 in_normal;

//Outputs
out vec3 ex_pos;
out vec2 ex_uv;
out vec3 ex_normal;


uniform mat4 MVP;

void main(void) 
{
	ex_pos=in_pos;
	ex_uv = in_uv;
	ex_normal = normalize(vec4(in_normal, 0.0).xyz);
	gl_Position = MVP * vec4(in_pos, 1.0);
}