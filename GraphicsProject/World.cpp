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
	//Initalizes the obj mesh
	m_objMesh.load("Lucy.obj", false);
	//Initialized the quad;
	m_quad.start();
	//Inotializes the light
	m_light.setDirection(glm::vec3(-1.0f));
	m_light.setAmbient(glm::vec4(0.6f, 0.66, 0.0f, 1.0f));
	m_light.setDiffuse(glm::vec4(0.6f, 0.6f, 1.0f, 1.0f));
	m_light.setSpecular(glm::vec4(glm::vec4(0.1f, 1.0f, 0.1f, 1.0f)));
	m_light.setSpecularPower(1.0f);

	//create camera transforms
	Transform cameraTransform = m_camra.getTransform();
	cameraTransform.setPosition(glm::vec3(1.0f));
	cameraTransform.setRotation(glm::vec3(45.0f, -45.0f, 0.0f));
	m_camra.setTransform(cameraTransform);
	/*m_camra.setTransform(glm::lookAt(
		glm::vec3(5.f, 5.0f, 5.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	));*/

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

	float cameraSpeed = 1.0f;

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
		Transform cameraTransform = m_camra.getTransform();
		cameraTransform.rotate(glm::vec3(deltaMouseY, deltaMouseX, 0.0f)  * (float)(cameraSpeed * deltaTime));
		m_camra.setTransform(cameraTransform);
	}

	//store yje previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;

	//get input 
	if (glfwGetKey(m_window, keyForward))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(cameraForward * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyBack))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(-cameraForward * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyRight))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(cameraRight * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyLeft))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(-cameraRight * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyUp))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(cameraUp * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
	if (glfwGetKey(m_window, keyDown))
	{
		//moveforward
		Transform cameraTranform = m_camra.getTransform();
		cameraTranform.translate(glm::vec3(-cameraUp * cameraSpeed * (float)deltaTime));
		m_camra.setTransform(cameraTranform);
	}
}

void World::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("cameraPosition",m_camra.getTransform().getPosition());
	shader->bindUniform("lightDirection", m_light.getDirection());
	shader->bindUniform("lightAmbient", m_light.getAmbient());
	shader->bindUniform("lightDiffuse", m_light.getDiffuse());
	shader->bindUniform("lightSpecular", m_light.getSpecular());
	shader->bindUniform("lightSpecularPower", m_light.getSpecularPower());
	/*m_quad.draw(shader);*/
	shader->bindUniform("modelMatrix", m_objTransform);
	m_objMesh.draw();
}

void World::end()
{
}

glm::mat4 World::getProjectionVeiw()
{
	return m_projectionMatrix * m_camra.getTransform().getMatrix();
}
