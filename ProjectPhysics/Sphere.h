#pragma once
#include "RigidBody.h"
#include "glm/vec4.hpp"

class Sphere :
	public RigidBody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color);
	~Sphere();

	virtual void draw();

	float getRadius() { return m_radius; }
	glm::vec4 getColor() { return m_color; }

private:
	float m_radius;
	glm::vec4 m_color;
};

