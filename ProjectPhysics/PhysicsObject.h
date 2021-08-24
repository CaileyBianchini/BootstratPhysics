#pragma once
#include "glm/vec2.hpp"

enum class ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	LENGTH
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void readPosition() {};

	ShapeType getShapeID() { return m_shapeID;  }

private:
	ShapeType m_shapeID;
};

