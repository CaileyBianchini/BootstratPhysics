#include "Engine.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include <iostream>
#include "World.h"

Engine::Engine() : Engine(1280, 720, "Window")
{
}
Engine::Engine(int width, int height, const char* tittle)
{
	m_world = new World(width, height);
	m_world->setWindow(m_window);
	m_width = width;
	m_height = height;
	m_tittle = tittle;
	
	m_shader = new aie::ShaderProgram();
}
Engine::~Engine()
{
	delete m_world;
	delete m_shader;
}
int Engine::run()
{
	int exitCode = 0;

	double currentTime = 0.0f;
	double previousTime = 0.0f;
	double deltaTime = 0.0f;

	//start
	exitCode = start();
	if (exitCode)
		return exitCode;

	//update
	while (!getGameOver())
	{
		//get the current time
		currentTime = glfwGetTime();
		//find the change in time
		deltaTime = currentTime - previousTime;
		//store the current time for the next loop
		previousTime = currentTime;

		exitCode = update(deltaTime);
		if (exitCode)
			return exitCode;
		exitCode = draw(m_shader);
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
	m_shader->loadShader(
		aie::eShaderStage::VERTEX,
		"simplevert.shader"
	);
	m_shader->loadShader(
		aie::eShaderStage::FRAGMENT,
		"simplefrag.shader"
	);
	if (!m_shader->link())
	{
		printf("Shader error: %s\n", m_shader->getLastError());
		return -10;
	}

	m_world->setWindow(m_window);
	m_world->start();

	return 0;
}

int Engine::update(double deltaTime)
{
	if (!m_window)return -4;

	glfwPollEvents();

	m_world->update(deltaTime);

	return 0;
}

int Engine::draw(aie::ShaderProgram* shader)
{
	if (!m_window)return -5;

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();

	m_shader->bindUniform("projectionViewModel", m_world->getProjectionVeiw());

	m_world->draw(shader);

	glfwSwapBuffers(m_window);

	return 0;
}

int Engine::end()
{
	if (!m_window)return -6;

	m_world->end();

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
