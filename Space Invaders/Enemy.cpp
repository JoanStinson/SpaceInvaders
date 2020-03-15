#include "Enemy.h"

#include "Application.h"

#include <functional>

Enemy::Enemy(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Creature(texture, rect, position, health, damage, speed)
{
	type = Type::ENEMY;
}

Enemy::~Enemy()
{
}

UpdateStatus Enemy::Update(float delta_time)
{
	App->clock.Invoke(0.75f, std::bind(&Enemy::Move, this));

	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
	return UpdateStatus();
}

void Enemy::Move()
{
	// When enemy reaches limits, change its direction (bounce)
	if ((position.x >= RIGHT_LIMIT || position.x <= LEFT_LIMIT) && !jump_frame)
	{
		speed = -speed;

		// When reaching bounce limit, jump down (move Y axis)
		if (++bounces_count > BOUNCE_LIMIT && position.y < BOTTOM_LIMIT)
		{
			position.y += rect.h;
			bounces_count = 0;
			jump_frame = true;
			return; // skip movement on X axis
		}
	}

	jump_frame = false;

	position.x += speed;
}
