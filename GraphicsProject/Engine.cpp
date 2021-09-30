#include "Engine.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include <iostream>


Engine::Engine() : Engine(1280, 720, "Window")
{
}
Engine::Engine(int width, int height, const char* tittle)
{
	m_width = width;
	m_height = height;
	m_tittle = tittle;
}
Engine::~Engine()
{
}
int Engine::run()
{
	int exitCode = 0;

	//start
	exitCode = start();
	if (exitCode)
		return exitCode;

	//update
	while (!getGameOver())
	{
		exitCode = update();
		if (exitCode)
			return exitCode;
		exitCode = draw();
		if (exitCode)
			return exitCode;
	}

	exitCode = end();
	if (exitCode)
		return exitCode;
	return 0;
}

int Engine::start()
{
	//initialyze
	if (glfwInit() == GLFW_FALSE)
		return -1;

	//creates a window
	m_window = glfwCreateWindow(m_width, m_height, m_tittle, nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(m_window);

	//loads OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}

	int majorVersion = ogl_GetMajorVersion();
	int minorVersion = ogl_GetMinorVersion();
	printf("OpenGL version: %i.%i\n", majorVersion, minorVersion);

	//initalizes the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//initializes the shader
	m_shader.loadShader(
		aie::eShaderStage::VERTEX,
		"simplevert.shader"
	);
	m_shader.loadShader(
		aie::eShaderStage::FRAGMENT,
		"simplefrag.shader"
	);
	if (!m_shader.link())
	{
		printf("Shader error: %s\n", m_shader.getLastError());
		return -10;
	}

	//Initialized the quad
	m_quad.start();

	//create camera transforms
	m_viewMatrix = glm::lookAt(
		glm::vec3(10.f, 10.0f, 10.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	m_projectionMatrix = glm::perspective(
		glm::pi<float>() / 4.0f,
		(float)m_width / (float)m_height,
		0.001f,
		1000.0f
	);

	return 0;
}

int Engine::update()
{
	if (!m_window)return -4;
	glfwPollEvents();
	return 0;
}

int Engine::draw()
{
	if (!m_window)return -5;

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.bind();

	glm::mat4 projectionViewModel = m_projectionMatrix * m_viewMatrix * m_quad.getTransformed();

	m_shader.bindUniform("projectionViewModel", projectionViewModel);

	m_quad.draw();

	glfwSwapBuffers(m_window);

	return 0;
}

int Engine::end()
{
	if (!m_window)return -6;

	//cleans up and exits
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}

bool Engine::getGameOver()
{
	if (!m_window)return true;

	bool condition = glfwWindowShouldClose(m_window);
	condition = condition || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	return condition;
}
