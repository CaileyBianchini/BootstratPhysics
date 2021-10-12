#include "World.h"
#include "gl_core_4_4.h"
#include "glm/ext.hpp"

World::World(int width, int height)
{
	m_width = width;
	m_height = height;
}

void World::start()
{
	//Initialized the quad;
	/*m_quad.setTansform(glm::mat4(10.0f));*/
	m_quad.start();

	if(!m_earthDifuse.load("earth_diffuse.jpg"))
	{ printf("Oopsies! Earth Diffuse didn't load! \n");}

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
	int program = -1;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	if (program == -1)
		printf("no shader bound. \n");

	int diffuseTextureUniform = glGetUniformLocation(program, "diffuseTexture"); //this is where diffuse texture is located
	if (diffuseTextureUniform >= 0)
		glUniform1i(diffuseTextureUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_earthDifuse.getHandle());

	m_quad.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionViewMode1()
{
	return m_projectionMatrix * m_camra.getVeiwMatrix() * m_quad.getTransform();
}
