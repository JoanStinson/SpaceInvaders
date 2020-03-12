#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"

#include <SDL.h>

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	spaceship = { 0, 0, 102, 102 };
	position = { (float)(SCREEN_WIDTH / 2) - (spaceship.w / 2), (float)SCREEN_HEIGHT - spaceship.h };
}

ModulePlayer::~ModulePlayer()
{
}

bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->LoadImage("Game/Player/spaceship.png");

	return true;
}

UpdateStatus ModulePlayer::Update()
{
	currentTime = SDL_GetTicks();

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

	App->renderer->Blit(graphics, position.x, position.y, &spaceship, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}
