#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "Point.h"

Player::Player()
{
}

Player::Player(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, rect_collider, texture, animation, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::PLAYER;

	SDL_Texture* bullet_texture = App->textures->LoadImage("Sprites/bullet.png");
	SDL_Texture* bullet_texture_death = App->textures->LoadImage("Sprites/blue.png");
	Animation bullet_animation_death(17, 64, 0.8f);

	pooled_bullets.reserve(MAX_BULLETS);

	for (int i = 0; i < MAX_BULLETS; ++i)
		pooled_bullets.push_back(new Bullet({ 0, 0, 32, 32 }, { 8, 8, 16, 16 }, bullet_texture, bullet_texture_death, bullet_animation_death, fPoint(), 1, 1, 0.5f, this));
}

Player::~Player()
{
	for (int i = 0; i < pooled_bullets.size(); ++i)
		delete pooled_bullets[i];
}

UpdateStatus Player::Update(float delta_time)
{
	if (!alive)
	{
		if (!animation_death.HasAnimationEnded())
		{
			App->renderer->Draw(texture_death, position, &(animation_death.GetCurrentFrameOnce()));
		}
		else
		{
			alive = true;
			animation_death.ResetAnim();
		}
	}
	else
	{
		// Move right
		if (App->input->GetKey(SDL_SCANCODE_RIGHT))
		{
			position.x += move_speed * delta_time;

			if (position.x > RIGHT_LIMIT)
				position.x = RIGHT_LIMIT;

			Entity::UpdateRectCollider();
		}
		// Move left
		else if (App->input->GetKey(SDL_SCANCODE_LEFT))
		{
			position.x -= move_speed * delta_time;

			if (position.x < LEFT_LIMIT)
				position.x = LEFT_LIMIT;

			Entity::UpdateRectCollider();
		}

		Entity::DrawAnimation();

		// Shoot pooled bullets
		if (App->input->GetKeyDown(SDL_SCANCODE_SPACE))
		{
			for (int i = 0; i < pooled_bullets.size(); ++i)
			{
				Bullet* bullet = pooled_bullets[i];

				// Instead of new/delete, enable/disable
				if (!bullet->enabled)
				{
					bullet->enabled = true;
					bullet->alive = true;
					bullet->SetPosition(fPoint{ position.x + 14, position.y - 16 });
					break;
				}
			}
		}

		// Update enabled shot bullets
		for (int i = 0; i < pooled_bullets.size(); ++i)
		{
			Bullet* bullet = pooled_bullets[i];

			if (bullet->enabled)
				bullet->Update(delta_time);
		}
	}

	return UpdateStatus::CONTINUE;
}
