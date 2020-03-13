#include "Bullet.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

Bullet::Bullet()
{
	rect = { 0, 0, 26, 26 };
	position = { float((SCREEN_WIDTH / 2) - (rect.w / 2)), float(SCREEN_HEIGHT - (rect.h*2)) };
}

bool Bullet::Start()
{
	LOG("Loading bullet");

	texture = App->textures->LoadImage("Game/Player/bullet.png");

	return true;
}

UpdateStatus Bullet::Update()
{
	App->renderer->Draw(texture, position, &rect, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool Bullet::CleanUp()
{
	LOG("Unloading bullet");

	SDL_DestroyTexture(texture);

	return true;
}
