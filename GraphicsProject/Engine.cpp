#include "Engine.h"
#include "GLFW/glfw3.h"
int Engine::run()
{
	return 0;
}

int Engine::start()
{
	int exitCode = 0;

	exitCode = start();
	if (exitCode)
		return exitCode;

	exitCode = end();
	if (exitCode)
		return exitCode;

	return 0;
}

int Engine::update()
{
	return 0;
}

int Engine::end()
{
	return 0;
}

bool Engine::getGameOver()
{
	bool condition = glfwWindowShouldClose(m_window);
	condition = condition || glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}
