// A simple vertex shader
#version 410

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNormal;

uniform mat4 projectionViewModel;
uniform mat4 modelMatrix;

out vec4 fPosition;
out vec4 fColor;
out vec3 fNormal;

void main()
{
	fPosition = vPosition;
	fColor = vColor;
	fNormal = (modelMatrix * vNormal).xyz;
	gl_Position = projectionViewModel * modelMatrix* vPosition;
}