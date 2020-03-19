#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

Player::Player(SDL_Texture* texture, Animation animation, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Creature(texture, animation, rect, position, health, damage, speed)
{
	type = Type::PLAYER;

	pooled_bullets.reserve(MAX_BULLETS);

	// Load bullet texture once, instead of MAX_BULLETS times
	SDL_Texture* bullet_texture = App->textures->LoadImage("Sprites/bullet.png");

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet* bullet = new Bullet(bullet_texture, SDL_Rect{ 0, 0, 32, 32 }, fPoint(), 1, 1, 0.1f, Type::PLAYER);
		pooled_bullets.push_back(bullet);
	}
}

Player::~Player()
{
	for (int i = 0; i < pooled_bullets.size(); ++i)
	{
		delete pooled_bullets[i];
	}
}

UpdateStatus Player::Update(float delta_time)
{
	// Move right
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += speed * delta_time;

		if (position.x > SCREEN_WIDTH - rect.w - 15)
			position.x = (float)SCREEN_WIDTH - rect.w - 15;

		Creature::UpdateBoxCollider();
	}
	// Move left
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= speed * delta_time;

		if (position.x < 0 + 15)
			position.x = 0 + 15;

		Creature::UpdateBoxCollider();
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

	Entity::DrawAnimation();

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
