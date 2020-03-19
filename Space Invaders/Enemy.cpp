#include "Enemy.h"

#include "Application.h"
#include "ModuleRender.h"

Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, texture, animation, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::ENEMY;
}

Enemy::~Enemy()
{
}

UpdateStatus Enemy::Update(float delta_time)
{
	if (life_points < 1)
	{
		if (!animation_death.HasAnimationEnded())
		{
			App->renderer->Draw(texture_death, position, &(animation_death.GetCurrentFrameOnce()));
		}
		else
		{
			alive = false;
		}
	}
	else
	{
		Entity::DrawAnimation();
	}

	Entity::UpdateBoxCollider();

	return UpdateStatus::CONTINUE;
}

void Enemy::Move(iPoint position)
{
	// When enemy reaches limits, change its direction (bounce)
	if ((position.x >= RIGHT_LIMIT || position.x <= LEFT_LIMIT) && !jump_frame)
	{
		move_speed = -move_speed;

		// When reaching bounce limit, jump down (move Y axis)
		if (++bounces_count > BOUNCE_LIMIT && (position.y <= BOTTOM_LIMIT && position.y > 0))
		{
			this->position.y += rect.h;
			bounces_count = 0;
			jump_frame = true;
			return; // skip movement on X axis
		}
	}

	jump_frame = false;

	this->position.x += move_speed;
}
