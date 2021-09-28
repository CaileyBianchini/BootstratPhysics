#include "Engine.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
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
