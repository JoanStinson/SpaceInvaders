#include "Enemy.h"

#include "Application.h"

#include <functional>

Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed, int column, int max_column) :
	Creature(texture, rect, position, health, damage, speed), column(column), max_column(max_column)
{
	type = Type::ENEMY;
	offset = max_column - column;
	offset *= rect.w;
}

Enemy::~Enemy()
{
}

UpdateStatus Enemy::Update(float delta_time)
{
	clock.Tick();

	//clock.Invoke(0.75f, std::bind(&Enemy::Move, this));

	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
	return UpdateStatus::CONTINUE;
}

void Enemy::Draw()
{
	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
}

void Enemy::Move(float row_rect_pos, float posy)
{
	// When enemy reaches limits, change its direction (bounce)
	if ((row_rect_pos >= 72 || row_rect_pos <= 11) && !jump_frame)
	{
		speed = -speed;

		// When reaching bounce limit, jump down (move Y axis)
		if (++bounces_count > BOUNCE_LIMIT && posy <= 204)
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
