#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0,0))
{
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.insert(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	m_actors.erase(actor);
}

void PhysicsScene::update(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	//as long as there is enough accumulated time for a fixed update...
	while (accumulatedTime >= m_timeStep) 
	{
		//...call each actor's fixedUpdate
		for (PhysicsObject* actor : m_actors)
		{
			actor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		auto outerEnd = m_actors.end();
		outerEnd--;
		for (auto outer = m_actors.begin(); outer !=outerEnd; outer++)
		{
			auto innerBegin = outer;
			innerBegin++;
			for (auto inner = ++outer; inner != m_actors.end(); inner++)
			{
				PhysicsObject* object1 = *outer;
				PhysicsObject* object2 = *inner;
				//collision detection
				sphereToSphere(dynamic_cast<Sphere*>(object1), dynamic_cast<Sphere*>(object2));
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
	{
		actor->draw();
	}
}

bool PhysicsScene::sphereToSphere(Sphere* sphere1, Sphere* sphere2)
{
	//Return true if there is collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		//TODO the nessecary maths here
		glm::vec1 position1 = sphere1->getPosition();
		glm::vec2 position2 = sphere2->getPosition();
		glm::vec2 distanceVec = position1 - position2;
		float distance = glm::sqrt((distanceVec.x * distanceVec.x) + (distanceVec.y * distanceVec.y));
		//TODO if the spheres touch, set their velocities to zero for now
		if (glm::abs(distance) < (sphere1->getRadius() +  sphere2->getRadius()))
		{
			//stopping collision
			sphere1->applyForce(-(sphere1->getVelocity() * sphere2->getMass()));
			sphere2->applyForce(-(sphere2->getVelocity() * sphere1->getMass()));
			////flying collision
			//sphere1->applyForceToOther(sphere2, sphere1->getVelocity() * sphere1->getMass());
			//sphere2->applyForceToOther(sphere1, sphere2->getVelocity() * sphere2->getMass() );

			return true;
		}
	}
	return false;
}
