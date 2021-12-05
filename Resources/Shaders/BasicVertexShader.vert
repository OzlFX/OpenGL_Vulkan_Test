#version 330 core

layout(location = 0) in vec3 in_Pos;
layout(location = 1) in vec4 in_Colour;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 out_Colour;
out vec3 out_Pos;

void main()
{
	out_Colour = in_Colour;
	out_Pos = in_Pos;
	gl_Position = u_ViewProjection * u_Transform * vec4(in_Pos, 1.0);
}