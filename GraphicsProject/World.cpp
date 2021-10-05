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
	m_camra.setTransform(glm::lookAt(
		glm::vec3(5.f, 5.0f, 5.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	));

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

void World::draw(aie::ShaderProgram* shader)
{
	m_quad.draw(shader);
}

void World::end()
{
}

glm::mat4 World::getProjectionVeiw()
{
	return m_projectionMatrix * m_camra.getTransform();
}
