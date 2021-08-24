#include "RigidBody.h"
#include "glm/ext.hpp"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) : PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_orientation = orientation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep);
}

void RigidBody::applyForce(glm::vec2 force)
{
	glm::vec2 acceleration = force / m_mass;
	m_velocity += acceleration;
}

void RigidBody::applyForceToOther(RigidBody* other, glm::vec2 force)
{
	other->applyForce(force);
	applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* other)
{
	//j = (-(1+ e)Vrel) dot n / (n dot (n * (1 / MA + 1 / MB))
	//j is the impulse magnitude
	//e is the coefficient of elasticity
	//Vrel is the relative velocity before collision
	//n is the collision normal
	//MA is the mass o of object A
	//MB is the mass of object B

	float elasticity = 1.0f;
	glm::vec2 relativeVelocity = other->getVelocity() - getVelocity();
	glm::vec2 collisionNormal = glm::normalize(other->getPosition() - getPosition());
	float massA = getMass();
	float massB = other->getMass();

	float impulse = glm::dot((-(1 + elasticity) * relativeVelocity), collisionNormal)
		/ glm::dot(collisionNormal, (collisionNormal * (1 / massA + 1 / massB)));

	applyForceToOther(other, collisionNormal * impulse);
}
