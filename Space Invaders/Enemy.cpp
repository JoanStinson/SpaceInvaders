#include "Enemy.h"

#include "Application.h"
#include "ModuleTextures.h"

Enemy::Enemy()
{
}

Enemy::Enemy(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, rect_collider, texture, animation, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::ENEMY;

	SDL_Texture* bullet_texture = App->textures->LoadImage("Sprites/bullet_enemy.png");
	SDL_Texture* bullet_texture_death = App->textures->LoadImage("Sprites/red.png");
	Animation bullet_animation_death(17, 64, 0.8f);

	pooled_bullets.reserve(MAX_BULLETS);

	for (int i = 0; i < MAX_BULLETS; ++i)
		pooled_bullets.push_back(new Bullet({ 0, 0, 32, 32 }, { 8, 8, 16, 16 }, bullet_texture, bullet_texture_death, bullet_animation_death, fPoint(), 1, 1, -0.25f, this));

	rect_collider_grid = { (int)position.x, (int)position.y, rect.w, rect.h };
}

Enemy::~Enemy()
{
}

UpdateStatus Enemy::Update(float delta_time)
{
	if (!DrawAnimationDeath(life_points < 1, position))
		DrawAnimation();

	rect_collider_grid.x = position.x; 
	rect_collider_grid.y = position.y; 

	UpdateRectCollider();

	// Update enabled shot bullets
	for (int i = 0; i < pooled_bullets.size(); ++i)
	{
		Bullet* bullet = pooled_bullets[i];

		if (bullet->enabled)
			bullet->Update(delta_time);
	}

	return UpdateStatus::CONTINUE;
}

void Enemy::OnDeath()
{
	alive = false;
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

void Enemy::Shoot()
{
	LOG("%f", position.x);

	// Shoot pooled bullets
	for (int i = 0; i < pooled_bullets.size(); ++i)
	{
		Bullet* bullet = pooled_bullets[i];

		// Instead of new/delete, enable/disable
		if (!bullet->enabled)
		{
			bullet->enabled = true;
			bullet->alive = true;
			bullet->SetPosition(fPoint{ position.x + 16, position.y + 34 });
			break;
		}
	}
}

SDL_Rect Enemy::GetRectColliderGrid() const
{
	return rect_collider_grid;
}
