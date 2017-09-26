#version 450 core 
layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;

out vec4 color;

void main()
{
	color = in_color;
	gl_Position = in_position*rotationMatrix*translationMatrix*rotationMatrix;
}