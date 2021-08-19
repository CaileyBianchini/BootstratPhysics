#pragma once
#include "PhysicsObject.h"
class RigidBody :
	public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float  timeStep);

	void applyForce(glm::vec2 force);
	void applyForceToOther(RigidBody* other, glm::vec2 force);

	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getOrientation() { return m_orientation; }
	float getMass() { return m_mass; }

private:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_orientation;
	float m_mass;
};
