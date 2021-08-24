#pragma once
#include "PhysicsObject.h"
#include "glm/vec4.hpp"

class Plane :
	public PhysicsObject
{
public:
	Plane(glm::vec2 normal, float distance, glm::vec4 color);
	~Plane();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void draw();
	
	glm::vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distance;  }
	glm::vec4 getColor() { return m_color; }

private:
	glm::vec2 m_normal;
	float m_distance;
	glm::vec4 m_color;
};

