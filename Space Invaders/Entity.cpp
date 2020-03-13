#include "Entity.h"

Entity::Entity() : active(true), life_points(3), rect({0, 0, 0, 0}), speed(0.1f)
{
}

Entity::Entity(fPoint position, float speed) : position(position), speed(speed), active(false), life_points(3), rect({ 0, 0, 0, 0 })
{
}

Entity::~Entity()
{
}

bool Entity::IsEnabled() const
{
	return active;
}

void Entity::SetPosition(fPoint new_position)
{
	position = new_position;
}

void Entity::SetActive(bool active)
{
	this->active = active;
}

void Entity::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
