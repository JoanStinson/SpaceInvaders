#include "Bullet.h"

#include "Application.h"
#include "ModuleSceneGame.h"

#include <SDL_rect.h>

Bullet::Bullet(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed, Entity* owner) :
	Creature(texture, rect, position, health, damage, speed), owner(owner)
{
	type = Type::BULLET;
	enabled = false;
}

Bullet::Bullet(SDL_Texture* texture, Animation animation, SDL_Rect rect, fPoint position, int health, int damage, float speed, Entity* owner) :
	Creature(texture, animation, rect, position, health, damage, speed), owner(owner)
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



	// Top limit
	if (position.y < rect.w)
	{
		Entity::DrawAnimation();
	}
	else
	{
		Entity::DrawEntity();
	}
		//enabled = false;

	// Collisions
	auto entities = App->sceneGame->GetEntities();

	for (auto& entity : entities)
	{
		if (!entity->enabled) continue;

		if ((/*entity->CompareType(Type::ASTEROID) ||*/ entity->CompareType(Type::ENEMY)) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
		{
			enabled = false;

			entity->health--;

			if (entity->health < 1)
			{
				entity->enabled = false;
				dynamic_cast<Player*>(owner)->score += 10;
			}
				

				//App->sceneGame->RemoveEntity(entity);

			

			break;
		}

		if (entity->CompareType(Type::ASTEROID) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
		{
			enabled = false;

			entity->health--;
			break;
		}
	}

	return UpdateStatus::CONTINUE;
}
