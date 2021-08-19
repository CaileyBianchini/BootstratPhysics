#include "PhysicsGame.h"
#include "Sphere.h"
#include "Input.h"
#include "Font.h"
#include "Gizmos.h"
#include <glm/ext.hpp>

bool PhysicsGame::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_renderer = new aie::Renderer2D();
	setBackgroundColour(0.4f, 0.5f, 0.1f, 0.0f);

	m_font = new aie::Font("../bin/font/consolas_bold.ttf", 32);

	m_scene = new PhysicsScene();
	m_scene->setTimeStep(0.01f);
	m_scene->setGravity({0.0f, 0.0f});

	Sphere* ball = new Sphere(glm::vec2 (), glm::vec2(), 1, 10, glm::vec4(0.5f, 0.2f, 1.0f, 1.0f));
	m_scene->addActor(ball);

	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_scene;
	delete m_font;
}

void PhysicsGame::update(float deltaTime)
{
	//get the input instance
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_scene->update(deltaTime);

	//exit on Esc
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)){
		quit();
	}
}

void PhysicsGame::draw()
{
	clearScreen();

	m_renderer->begin();

	//Draw the scene
	m_scene->draw();

	//Draw the Gizmos
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(
		-100,						//left
		100,							//right
		-100 / aspectRatio, //bottom
		100 / aspectRatio,  //top
		-1.0f,						//zNear
		1.0f							//zFar
		));

	//Draw fps
	/*m_renderer->setRenderColour(1.0f, 0.5f, 0.6f, 1.0f);*/
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->drawText(m_font, fps, 0.0f, 10.0f);

	m_renderer->end();
}
