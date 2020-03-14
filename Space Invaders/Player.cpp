#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include "SDL_Button.h"

Player::Player()
{
	rect = { 0, 0, 102, 102 };
	position = { float((SCREEN_WIDTH / 2) - (rect.w / 2)), float(SCREEN_HEIGHT - rect.h) };

	tag = Tag::PLAYER;

	box_collider.x = position.x;
	box_collider.y = position.y;
	box_collider.w = rect.w;
	box_collider.h = rect.h;

	speed = 0.5f;

	pooled_bullets.reserve(MAX_BULLETS);
}

Player::Player(fPoint position, float speed) : Creature(position, speed)
{
	rect = { 0, 0, 102, 102 };
}

Player::~Player()
{
}

bool Player::Start()
{
	LOG("Loading player");

	// Load bullet texture once, instead of MAX_BULLETS times
	SDL_Texture* bulletTexture = App->textures->LoadImage("Game/Player/bullet.png");

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->SetTexture(bulletTexture);
		bullet->Start();
		pooled_bullets.push_back(bullet);
		App->sceneGame->AddEntity(bullet);
	}

	texture = App->textures->LoadImage("Game/Player/spaceship.png");

	return true;
}

UpdateStatus Player::Update(float delta_time)
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += speed * delta_time;

		if (position.x > SCREEN_WIDTH - rect.w)
			position.x = (float)SCREEN_WIDTH - rect.w;

		box_collider.x = position.x;
		box_collider.y = position.y;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= speed * delta_time;

		if (position.x < 0)
			position.x = 0;

		box_collider.x = position.x;
		box_collider.y = position.y;
	}

	if (App->input->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		// Shoot pooled projectile
		for (unsigned i = 0; i < pooled_bullets.size(); ++i)
		{
			Bullet* bullet = pooled_bullets[i];

			// Instead of new/delete, enable/disable
			if (!bullet->IsEnabled())
			{
				bullet->SetActive(true);
				bullet->SetPosition(position);
				break;
			}
		}
	}

	// Draw box collider
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &box_collider);

	App->renderer->Draw(texture, position, &rect);

	return UpdateStatus::CONTINUE;
}

bool Player::CleanUp()
{
	LOG("Unloading player");

	return true;
}
