#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "Animation.h"
#include "ModuleRender.h"

Player::Player()
{
}

Player::Player(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, texture, animation, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::PLAYER;

	SDL_Texture* bullet_texture = App->textures->LoadImage("Sprites/bullet.png");
	SDL_Texture* bullet_texture_death = App->textures->LoadImage("Sprites/blue.png");
	Animation bullet_animation_death(17, 64, 0.5f);

	pooled_bullets.reserve(MAX_BULLETS);

	for (int i = 0; i < MAX_BULLETS; ++i)
		pooled_bullets.push_back(new Bullet({ 0, 0, 32, 32 }, bullet_texture, bullet_texture_death, bullet_animation_death, fPoint(), 1, 1, 0.1f, this));
}

Player::~Player()
{
	for (int i = 0; i < pooled_bullets.size(); ++i)
		delete pooled_bullets[i];
}

UpdateStatus Player::Update(float delta_time)
{
	// Move right
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += move_speed * delta_time;

		if (position.x > SCREEN_WIDTH - rect.w - 15)
			position.x = (float)SCREEN_WIDTH - rect.w - 15;

		Entity::UpdateBoxCollider();
	}
	// Move left
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= move_speed * delta_time;

		if (position.x < 0 + 15)
			position.x = 0 + 15;

		Entity::UpdateBoxCollider();
	}

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
				bullet->SetPosition(fPoint{ position.x + 14, position.y - 16 });
				break;
			}
		}
	}

	//Entity::DrawEntity();
	Entity::DrawAnimation();
	//App->renderer->Draw(texture, position, &(animation.frames[0]));

	// Update shooted bullets if enabled
	for (int i = 0; i < pooled_bullets.size(); ++i)
	{
		Bullet* bullet = pooled_bullets[i];

		if (bullet->enabled)
		{
			bullet->Update(delta_time);
		}
	}

	return UpdateStatus::CONTINUE;
}
