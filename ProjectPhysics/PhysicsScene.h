#pragma once
#include <set>
#include "glm/vec2.hpp"
#include "Sphere.h"
class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);

	void update(float deltaTime);
	void draw();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep;}
	float getTimeStep() const { return m_timeStep; }

	static bool sphereToSPhere(Sphere* sphere1, Sphere* sphere2);

private:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::set<PhysicsObject*> m_actors;
};

