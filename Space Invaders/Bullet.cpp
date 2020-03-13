#include "Bullet.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include <SDL.h>

Bullet::Bullet()
{
	rect = { 0, 0, 26, 26 };
	active = false;
	speed = 0.5f;
}

Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	LOG("Loading bullet");

	return true;
}

UpdateStatus Bullet::Update(float delta_time)
{
	if (active)
	{
		position.y -= speed * delta_time;

		App->renderer->Draw(texture, position, &rect, LAYER_FRONT);
	}

	if (position.y < rect.w && active)
	{
		active = false;
	}

	return UpdateStatus::CONTINUE;
}

bool Bullet::CleanUp()
{
	LOG("Unloading bullet");

	return true;
}
