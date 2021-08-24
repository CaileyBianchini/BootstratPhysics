#pragma once
#include <set>
#include "glm/vec2.hpp"
#include "Sphere.h"
#include "Plane.h"

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

	static bool planeToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool planeToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool planeToBox(PhysicsObject* object1, PhysicsObject* object2);
	static bool sphereToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool sphereToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool sphereToBox(PhysicsObject* object1, PhysicsObject* object2);
	static bool boxToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool boxToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool boxToBox(PhysicsObject* object1, PhysicsObject* object2);

private:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::set<PhysicsObject*> m_actors;
};

