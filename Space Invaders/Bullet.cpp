#include "Bullet.h"

#include "Application.h"

#include <SDL_rect.h>

Bullet::Bullet(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed, Type owner) :
	Creature(texture, rect, position, health, damage, speed), owner(owner)
{
	type = Type::BULLET;
	enabled = false;
}

Bullet::~Bullet()
{
}

UpdateStatus Bullet::Update(float delta_time)
{
	position.y -= speed * delta_time;

	Creature::UpdateBoxCollider();

	Entity::DrawEntity();

	// Top limit
	if (position.y < rect.w)
		enabled = false;

	// Collisions
	for (auto& entity : Entity::entities)
	{
		if (!entity->enabled) continue;

		if ((entity->CompareType(Type::ASTEROID) || entity->CompareType(Type::ENEMY)) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
		{
			enabled = false;

			entity->health--;

			if (entity->health < 1)
				entity->enabled = false;

				//Entity::RemoveEntity(entity);

			break;
		}
	}

	return UpdateStatus::CONTINUE;
}
