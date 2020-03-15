#include "Bullet.h"

#include "Application.h"

#include <SDL_rect.h>

Bullet::Bullet(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Creature(texture, rect, position, health, damage, speed)
{
	type = Type::BULLET;
	SetActive(false);
}

Bullet::~Bullet()
{
}

UpdateStatus Bullet::Update(float delta_time)
{
	position.y -= speed * delta_time;

	Creature::UpdateBoxCollider();

	Entity::DrawEntity();

	// Collisions
	for (auto& entity : Entity::entities)
	{
		if (!entity->IsActive()) continue;

		if (entity->CompareType(Type::ASTEROID) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
		{
			SetActive(false);

			entity->health--;

			if (entity->health < 1)
				Entity::RemoveEntity(entity);

			break;
		}
	}

	if (position.y < rect.w)
		SetActive(false);

	return UpdateStatus::CONTINUE;
}
