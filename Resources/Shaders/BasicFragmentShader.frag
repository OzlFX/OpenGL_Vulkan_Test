#version 330 core

layout(location = 0) out vec4 Colour;

in vec4 out_Colour;
in vec3 out_Pos;

uniform vec4 in_Colour;

void main()
{
	Colour = out_Colour;
}