#include "Entity.h"

Entity::Entity()
{
	m_parent = new Entity;
}

Entity::~Entity()
{
	delete m_parent;
}

void Entity::start()
{
}

void Entity::update()
{
}

void Entity::draw()
{
}

void Entity::end()
{
}

void Entity::updateGlobalTransform()
{

}
