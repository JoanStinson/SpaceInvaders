#include "Player.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Player::Player()
{
	spaceship = { 0, 0, 102, 102 };
	position = { float((SCREEN_WIDTH / 2) - (spaceship.w / 2)), float(SCREEN_HEIGHT - spaceship.h) };
	speed = 350.0f / FPS;
}

Player::Player(fPoint position, float speed) : Creature(position, speed)
{
	spaceship = { 0, 0, 102, 102 };
}

Player::~Player()
{
}

bool Player::Start()
{
	LOG("Loading player");

	graphics = App->textures->LoadImage("Game/Player/spaceship.png");

	return true;
}

UpdateStatus Player::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += speed;

		if (position.x > SCREEN_WIDTH - spaceship.w)
		{
			position.x = SCREEN_WIDTH - spaceship.w;
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
	}

	App->renderer->Draw(graphics, position, &spaceship, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool Player::CleanUp()
{
	LOG("Unloading player");

	SDL_DestroyTexture(graphics);

	return true;
}
