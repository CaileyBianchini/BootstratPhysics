#pragma once
#include "Shader.h"
#include "Mesh.h"

struct GLFWwindow;

class Engine
{
public:
	Engine();
	Engine(int width, int height, const char* tittle);
	~Engine();

	int run();


private:

	int start();
	int update();
	int draw();
	int end();

	bool getGameOver();

private:
	GLFWwindow* m_window = nullptr;
	int m_width, m_height;
	const char* m_tittle;

	aie::ShaderProgram m_shader;
	Mesh m_quad;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};