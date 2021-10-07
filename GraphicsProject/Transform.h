#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Transform
{
public:
	Transform() {}
	~Transform() {}

	void translate(glm::vec3 translation);
	void rotate(glm::vec3 rotation);
	void scale(glm::vec3 scale);

	glm::vec3 getPosition() { return m_position; }
	void setPosition(glm::vec3 position);
	glm::vec3 getRotation() { return m_rotation; }
	void setRotation(glm::vec3 rotation);
	glm::vec3 getScale() { return m_scale; }
	void setScale(glm::vec3 scale);

	glm::mat4 getMatrix();

private:
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f);

	glm::mat4 m_matrix = glm::mat4(1.0f);
	bool m_shouldUpdateMatrix = true;
};

