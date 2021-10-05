//A simple fragment shader
#version 410

in vec4 color;
in vec3 fNormal;

out vec4 FragColor;

void main()
{
	FragColor = color;
}