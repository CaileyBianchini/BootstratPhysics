#include "PhysicsGame.h"
#include "Input.h"
#include "Font.h"

bool PhysicsGame::startup()
{
	m_renderer = new aie::Renderer2D();
	setBackgroundColour(0.4f, 0.5f, 0.1f, 0.0f);
	m_font = new aie::Font("../bin/font/consolas_bold.ttf", 32);
	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_font;
}

void PhysicsGame::update(float deltaTime)
{
	//get the input instance
	aie::Input* input = aie::Input::getInstance();

	//exit on Esc
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)){
		quit();
	}
}

void PhysicsGame::draw()
{
	clearScreen();

	m_renderer->begin();

	//Draw fps
	m_renderer->setRenderColour(1.0f, 0.5f, 0.6f, 1.0f);
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->drawText(m_font, fps, 0.0f, 10.0f);

	m_renderer->end();
}
