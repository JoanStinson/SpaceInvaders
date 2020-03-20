#include "Bullet.h"

#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModuleRender.h"

#include <SDL_rect.h>

Bullet::Bullet()
{
}

Bullet::Bullet(SDL_Rect rect, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed, Entity* owner) :
	Entity(rect, texture, texture_death, animation_death, position, life_points, damage, move_speed), owner(owner)
{
	type = Type::BULLET;
	enabled = false;
}

Bullet::~Bullet()
{
}

UpdateStatus Bullet::Update(float delta_time)
{
	if (position.y <= TOP_LIMIT || position.y >= BOTTOM_LIMIT || !alive)
	{
		if (!animation_death.HasAnimationEnded())
		{
			App->renderer->Draw(texture_death, fPoint{ position.x - (rect.w / 2), position.y - (rect.w / 2) }, &(animation_death.GetCurrentFrameOnce()));
		}
		else
		{
			enabled = false;
			animation_death.ResetAnim();
		}
	}
	else
	{
		position.y -= move_speed * delta_time;

		Entity::UpdateBoxCollider();
		Entity::Draw();
		CheckCollisions();
	}

	return UpdateStatus::CONTINUE;
}

void Bullet::CheckCollisions()
{
	auto entities = App->sceneGame->GetEntities();

	for (auto& entity : entities)
	{
		if (!entity->enabled || !entity->alive) continue;

		if (SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
		{
			// Player shot bullet to asteroid or enemy
			if (owner->CompareType(Type::PLAYER) && (entity->CompareType(Type::ASTEROID) || entity->CompareType(Type::ENEMY)))
			{
				if (entity->CompareType(Type::ASTEROID))
					alive = false;
				else 
					enabled = false;

				entity->life_points--;

				if (entity->life_points < 1)
				{
					enabled = false;
					//entity->enabled = false;

					if (entity->CompareType(Type::ENEMY))
						dynamic_cast<Player*>(owner)->score += 10;

					if (entity->CompareType(Type::ASTEROID))
					{
						dynamic_cast<Player*>(owner)->asteroids_destroyed += 1;
					}

					//App->sceneGame->RemoveEntity(entity);
				}
				break;
			}
			// Enemy shot bullet to player
			else if (owner->CompareType(Type::ENEMY) && entity->CompareType(Type::PLAYER))
			{
				//alive = false;
				enabled = false;
				entity->life_points--;
				entity->alive = false;
				break;
			}
		}
	}
}
