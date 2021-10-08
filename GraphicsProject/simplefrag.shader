//A simple fragment shader
#version 410

in vec4 fColor; 
in vec2 fTexCoord;

uniform sampler2D diffuseTexture;

out vec4 pColor;

void main()
{
	pColor = fColor * texture(diffuseTexture, fTexCoord);
}