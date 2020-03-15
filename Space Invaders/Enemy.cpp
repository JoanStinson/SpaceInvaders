#include "Enemy.h"

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
	// Move enemy, if it reaches either left or right limit, change direction
	// Once it reaches both limits, decrease its Y position
	int RIGHT_LIMIT = SCREEN_WIDTH - rect.w;
	int LEFT_LIMIT = 0;

	if (position.x >= RIGHT_LIMIT || position.x <= LEFT_LIMIT)
	{
		speed = -speed;

	}
	position.x += speed * delta_time;

	LOG("%f", position.x);

	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
	return UpdateStatus();
}
