#include "Enemy.h"

#include "Application.h"

Enemy::Enemy()
{
}

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
	//TODO bullet shooting
	return UpdateStatus::CONTINUE;
}

void Enemy::Draw()
{
	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
}

void Enemy::Move(iPoint position)
{
	// When enemy reaches limits, change its direction (bounce)
	if ((position.x >= RIGHT_LIMIT || position.x <= LEFT_LIMIT) && !jump_frame)
	{
		speed = -speed;

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

	this->position.x += speed;
}
