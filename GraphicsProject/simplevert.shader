// A simple vertex shader
#version 410

layout(location = 0) in vec4 position;

uniform mat4 projectionViewModel;

void main()
{
	gl_Position = projectionViewModel * position;
}