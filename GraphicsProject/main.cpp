#include "Engine.h"
int main()
{
	Engine* engine = new Engine(1280, 720, "Graphics");

	int exitCode = engine->run();

	delete engine;

	return exitCode;
}
