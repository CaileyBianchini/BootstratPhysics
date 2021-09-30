#pragma once
#include "glm/mat4x4.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	void start();
	void update();
	void draw();
	void end();

	Entity* getParent() { return m_parent; }
	void setParent(Entity* parent) { m_parent = parent; }
	glm::mat4 getLocalTransform() { return m_localTransform; }
	void setLocalTransform(glm::mat4 transform) { m_localTransform = transform; }
	glm::mat4 getGlobalTransform() { return m_globalTransform; }

private:
	void updateGlobalTransform();

private:
	Entity* m_parent = nullptr;
	glm::mat4 m_localTransform = glm::mat4(1.0f);
	glm::mat4 m_globalTransform = glm::mat4(1.0f);
};

