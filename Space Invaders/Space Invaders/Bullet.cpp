#include "Bullet.h"

#include "Application.h"
#include "ModuleSceneGame.h"
#include "Asteroid.h"

Bullet::Bullet()
{
}

Bullet::Bullet(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed, Entity* owner) :
	Entity(rect, rect_collider, texture, texture_death, animation_death, position, life_points, damage, move_speed), owner(owner)
{
	type = Type::BULLET;
	enabled = false;
}

Bullet::~Bullet()
{
}

UpdateStatus Bullet::Update(float delta_time)
{
	bool condition_death = position.y <= TOP_LIMIT || position.y >= BOTTOM_LIMIT || !alive;

	fPoint position_death = owner->CompareType(Type::PLAYER) ? fPoint{ position.x - (rect.w / 2), position.y - (rect.w / 2) } : fPoint{ position.x - (rect.w / 2), position.y - 2 };

	if (DrawAnimationDeath(condition_death, position_death))
		return UpdateStatus::CONTINUE;

	position.y -= move_speed * delta_time;

	UpdateRectCollider();
	Draw();
	CheckCollisions();

	return UpdateStatus::CONTINUE;
}

void Bullet::OnDeath()
{
	enabled = false;
	animation_death.ResetAnim();
}

void Bullet::CheckCollisions()
{
	const auto& entities = App->scene_game->GetEntities();

	for (auto& entity : entities)
	{
		if (!entity->enabled || !entity->alive) continue;

		if (SDL_HasIntersection(&rect_collider, &entity->GetRectCollider()))
		{
			// Player shot bullet to asteroid or enemy
			if (owner->CompareType(Type::PLAYER))
			{
				if (entity->CompareType(Type::ASTEROID))
				{
					alive = false;
					entity->life_points--;

					if (entity->life_points < 1)
					{
						entity->alive = false;
						dynamic_cast<Asteroid*>(entity)->PlayKillSound();

						enabled = false;
					}
				}
				else if (entity->CompareType(Type::ENEMY))
				{
					enabled = false;
					entity->life_points--;

					if (entity->life_points < 1)
					{
						entity->alive = false;
						dynamic_cast<Enemy*>(entity)->PlayKillSound();

						App->scene_game->score += 10;

						if (App->scene_game->score > App->scene_game->hiscore)
							App->scene_game->hiscore = App->scene_game->score;

						if (App->scene_game->score % 180 == 0)
							App->scene_game->next_wave = true;
					}
				}
				break;
			}
			// Enemy shot bullet to player
			else if (owner->CompareType(Type::ENEMY) && entity->CompareType(Type::PLAYER))
			{
				enabled = false;
				dynamic_cast<Player*>(entity)->PlayKillSound();

				entity->alive = false;
				entity->life_points--;

				if (entity->life_points < 1)
				{
					entity->life_points = 0;
					App->scene_game->game_over = true;
					App->scene_game->PlayGameOverSound();
				}
				break;
			}
		}

	}
}
