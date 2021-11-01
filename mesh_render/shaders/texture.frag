#version 460

in vec2 ex_uv;

out vec4 color;

uniform sampler2D tex;

void main()
{
	color = texture(tex, ex_uv);
}