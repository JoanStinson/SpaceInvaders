#include "Enemy.h"

#include "Application.h"
#include "ModuleSceneGame.h"

#include <functional>
#include <cstdio>

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
	App->sceneGame->clock.Invoke(0.75f, std::bind(&Enemy::Move, this));

	Creature::UpdateBoxCollider();
	Entity::DrawEntity();
	return UpdateStatus();
}

void Enemy::Move()
{
	int RIGHT_LIMIT = SCREEN_WIDTH - rect.w;
	int LEFT_LIMIT = 0;
	int BOTTOM_LIMIT = SCREEN_HEIGHT - (rect.h * 4);
	static Uint8 num_times_limit_reached = 0;
	
	// Move enemy, if it reaches either left or right limit, change direction
	if (position.x >= RIGHT_LIMIT || position.x <= LEFT_LIMIT)
	{
		speed = -speed;

		// Once it reaches both limits, decrease its Y position
		if (++num_times_limit_reached > 0 && position.y < BOTTOM_LIMIT)
		{
			//position.x += -speed;
			position.y += rect.h;
			num_times_limit_reached = 0;
		}
	}

	position.x += speed;
}
