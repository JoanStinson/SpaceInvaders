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
	// Top limit
	if (position.y < rect.w + 70)
	{
		//position.y = position.y;
		if (!animation_death.HasAnimationEnded())
		{
			App->renderer->Draw(texture_death, fPoint{ position.x - 16, position.y - 16 }, &(animation_death.GetCurrentFrameOnce()));
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
		Entity::DrawEntity();

		// Collisions
		auto entities = App->sceneGame->GetEntities();

		for (auto& entity : entities)
		{
			if (!entity->enabled) continue;
			if (entity->dead) continue;

			if ((/*entity->CompareType(Type::ASTEROID) ||*/ entity->CompareType(Type::ENEMY)) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
			{
				enabled = false;

				entity->life_points--;

				if (entity->life_points < 1)
				{
					//entity->enabled = false;
					dynamic_cast<Player*>(owner)->score += 10;
				}

				//App->sceneGame->RemoveEntity(entity);
				break;
			}

			if (entity->CompareType(Type::ASTEROID) && SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
			{
				enabled = false;
				entity->life_points--;
				break;
			}
		}
	}

	return UpdateStatus::CONTINUE;
}
