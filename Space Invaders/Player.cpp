#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

Player::Player(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Creature(texture, rect, position, health, damage, speed)
{
	type = Type::PLAYER;

	pooled_bullets.reserve(MAX_BULLETS);

	// Load bullet texture once, instead of MAX_BULLETS times
	SDL_Texture* bullet_texture = App->textures->LoadImage("Game/Player/bullet.png");

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet* bullet = new Bullet(bullet_texture, SDL_Rect{ 0, 0, 26,26 }, fPoint(), 1, 1, 0.1f);
		pooled_bullets.push_back(bullet);
		Entity::AddEntity(bullet);
	}
}

Player::~Player()
{
}

UpdateStatus Player::Update(float delta_time)
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += speed * delta_time;

		if (position.x > SCREEN_WIDTH - rect.w)
			position.x = (float)SCREEN_WIDTH - rect.w;

		Creature::UpdateBoxCollider();
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= speed * delta_time;

		if (position.x < 0)
			position.x = 0;

		Creature::UpdateBoxCollider();
	}

	if (App->input->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		// Shoot pooled projectile
		for (unsigned i = 0; i < pooled_bullets.size(); ++i)
		{
			Bullet* bullet = pooled_bullets[i];

			// Instead of new/delete, enable/disable
			if (!bullet->IsActive())
			{
				bullet->SetActive(true);
				bullet->SetPosition(position);
				break;
			}
		}
	}

	Entity::DrawBoxCollider();
	Entity::DrawEntity();

	return UpdateStatus::CONTINUE;
}
