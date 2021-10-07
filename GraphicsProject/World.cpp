#include "World.h"
#include "glm/ext.hpp"
#include "GLFW/glfw3.h"

World::World(int width, int height)
{
	m_width = width;
	m_height = height;
}

void World::start()
{
	//Initialized the quad;
	m_quad.start();
	//Inotializes the light
	m_light.setDirection(glm::vec3(-1.0f));
	m_light.setAmbient(glm::vec4(0.6f, 0.66, 0.0f, 1.0f));
	m_light.setDiffuse(glm::vec4(0.6f, 0.6f, 1.0f, 1.0f));
	m_light.setSpecular(glm::vec4(glm::vec4(0.1f, 1.0f, 0.1f, 1.0f)));
	m_light.setSpecularPower(1.0f);

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

void World::update(double deltaTime)
{
	int keyForward = GLFW_KEY_W;
	int keyBack = GLFW_KEY_S;
	int keyLeft = GLFW_KEY_A;
	int keyRight = GLFW_KEY_D;
	int keyUp = GLFW_KEY_E;
	int keyDown = GLFW_KEY_Q;

	float cameraSpeed = 10.0f;




	//calculate the forward vector
		glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, 1.0f);
		//calculate the right vector
		glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
		//calculate the up vector
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//get current mouse coordinates
	glfwGetCursorPos(m_window, &m_currentMouseX, &m_currentMouseY);

	//rotate camera using change in mouse position
	double deltaMouseX = m_currentMouseX - m_previousMouseX;
	double deltaMouseY = m_currentMouseY - m_previousMouseY;
	if (deltaMouseX != 0.0 && deltaMouseY != 0.0)
	{
		glm::mat4 cameraTransform = m_camra.getTransform();

		cameraTransform = glm::rotate(
			cameraTransform, 
			(float)(deltaMouseX * deltaTime), 
			cameraUp);

		cameraTransform = glm::rotate(
			cameraTransform, 
			(float)(deltaMouseY * deltaTime), 
			cameraRight);

		m_camra.setTransform(cameraTransform);
	}

	//store yje previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;

	//get input 
	if (glfwGetKey(m_window, keyForward))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, cameraForward * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyBack))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, -cameraForward * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyRight))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, cameraRight * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyLeft))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, -cameraRight * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyUp))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, cameraUp * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyDown))
	{
		//moveforward
		glm::mat4 cameraTranform = m_camra.getTransform();
		cameraTranform = glm::translate(cameraTranform, -cameraUp * cameraSpeed * (float)deltaTime);
		m_camra.setTransform(cameraTranform);
	}
}

void World::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("cameraPosition", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	shader->bindUniform("lightDirection", m_light.getDirection());
	shader->bindUniform("lightAmbient", m_light.getAmbient());
	shader->bindUniform("lightDiffuse", m_light.getDiffuse());
	shader->bindUniform("lightSpecular", m_light.getSpecular());
	shader->bindUniform("specularPower", m_light.getSpecularPower());
	m_quad.draw(shader);
}

void World::end()
{
}

glm::mat4 World::getProjectionVeiw()
{
	return m_projectionMatrix * m_camra.getTransform();
}
