#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(fPoint position, float speed) : position(position), speed(speed)
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
