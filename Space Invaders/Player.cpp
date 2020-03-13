#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Player::Player()
{
	rect = { 0, 0, 102, 102 };
	position = { float((SCREEN_WIDTH / 2) - (rect.w / 2)), float(SCREEN_HEIGHT - rect.h) };
	speed = 350.0f / FPS;

	bullet = new Bullet();
}

Player::Player(fPoint position, float speed) : Creature(position, speed)
{
	rect = { 0, 0, 102, 102 };
}

Player::~Player()
{
	delete bullet;
}

bool Player::Start()
{
	LOG("Loading player");

	bullet->Start();

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
		//TODO shoot projectiles
		bullet->Update();
	}

	App->renderer->Draw(texture, position, &rect, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool Player::CleanUp()
{
	LOG("Unloading player");

	bullet->CleanUp();

	SDL_DestroyTexture(texture);

	return true;
}
