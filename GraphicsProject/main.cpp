#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include <iostream>

int main()
{
	//initialyze
	if (!glfwInit() == GLFW_FALSE)
		return -1;

	//creates a window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Window", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	//loads OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	int majorVersion = ogl_GetMajorVersion();
	int minorVersion = ogl_GetMinorVersion();
	printf("OpenGL version: %i.%i\n", majorVersion, minorVersion);

	//cleans up and exits
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
