//A simple fragment shader
#version 410

in vec4 fPosition;
in vec4 fColor;
in vec3 fNormal;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float lightSpecularPower;

uniform vec3 lightDirection;
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform float specularPower;

uniform vec4 cameraPosition;

out vec4 FragColor;

void main()
{
	vec3 surfaceNormal = normalize(fNormal);
	vec3 lightNormal = normalize(lightDirection);/*

	vec4 lightColor = vec4(1.0f, 1.0f, 0.6f, 1.0f);*/
	//lightNormal = normalize(vec3(-1.0f, -1.0f, -1.0f));

	//color = ambientColor + diffuseColor + specularColor
	vec4 ambientColor = vec4(Ka, 1.0f) * lightAmbient;

	//calculate diffuse color
	float lamberTerm = dot(-lightNormal, surfaceNormal);
	lamberTerm = max(0, min(1, lamberTerm));
	vec4 diffuseColor = vec4(Kd, 1.0f) * lightDiffuse * lamberTerm;

	//calculate specular color
	vec3 surfaceView = normalize(cameraPosition.xyz - fPosition.xyz);
	vec3 reflectionNormal = reflect(lightNormal, surfaceNormal);
	float specularTerm = dot(surfaceView, reflectionNormal);
	specularTerm = max(0, min(1, specularTerm));
	specularTerm = pow(specularTerm, specularPower);
	vec4 specularColor = vec4(Ks, 1.0f) * lightSpecular * specularTerm;

	FragColor = ambientColor + diffuseColor + specularColor;
}