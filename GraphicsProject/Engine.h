#pragma once
class Engine
{
public:
	Engine() {}
	~Engine() {}

	int run();


private:

	int start();
	int update();
	int end();

	bool getGameOver();

private:
	GLFWwindow* m_window;
};

