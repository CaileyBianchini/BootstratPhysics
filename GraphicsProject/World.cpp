#include "World.h"
#include "glm/ext.hpp"

World::World(int width, int height)
{
	m_width = width;
	m_height = height;
}

void World::start()
{
	//Initialized the quad;
	m_quad.start();

	//create camera transforms
	m_camra.setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
	m_camra.setTheta(-135.0f);
	m_camra.setPhi(-35.0f);

	m_projectionMatrix = glm::perspective(
		m_camra.getFeildOfVeiw() * glm::pi<float>() / 180.0f,
		(float)m_width / (float)m_height,
		m_camra.getNearClip(),
		m_camra.getFarClip()
	);
}

void World::update()
{
}

void World::draw()
{
	m_quad.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewMode1()
{
	return m_projectionMatrix * m_camra.getVeiwMatrix() * m_quad.getTransform();
}
