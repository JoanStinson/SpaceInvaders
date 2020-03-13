#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"

Player::Player()
{
	rect = { 0, 0, 102, 102 };
	position = { float((SCREEN_WIDTH / 2) - (rect.w / 2)), float(SCREEN_HEIGHT - rect.h) };
	speed = 350.0f / FPS;

	pooled_bullets.reserve(MAX_BULLETS);
}

Player::Player(fPoint position, float speed) : Creature(position, speed)
{
	rect = { 0, 0, 102, 102 };
}

Player::~Player()
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		delete pooled_bullets[i];
	}
}

bool Player::Start()
{
	LOG("Loading player");

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->Start();
		pooled_bullets.push_back(bullet);
	}

	texture = App->textures->LoadImage("Game/Player/spaceship.png");

	return true;
}

UpdateStatus Player::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += speed;

		if (position.x > SCREEN_WIDTH - rect.w)
		{
			position.x = SCREEN_WIDTH - rect.w;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= speed;

		if (position.x < 20)
		{
			position.x = 20;
		}
	}

	if (App->input->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		// Shoot pooled projectiles
		for (int i = 0; i < pooled_bullets.size(); ++i)
		{
			Bullet* bullet = pooled_bullets[i];

			// Instead of new/delete, enable/disable
			if (!bullet->IsEnabled())
			{
				bullet->SetActive(true);
				bullet->SetPosition(position);
				App->sceneGame->AddEntity(bullet);
				break;
			}
		}
	}

	App->renderer->Draw(texture, position, &rect, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool Player::CleanUp()
{
	LOG("Unloading player");

	SDL_DestroyTexture(texture);

	return true;
}
