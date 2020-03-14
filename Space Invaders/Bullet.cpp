#include "Bullet.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include <SDL.h>

Bullet::Bullet()
{
	boxCollider = rect = { 0, 0, 26, 26 };

	active = false;
	speed = 0.1f;
}

Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	LOG("Loading bullet");
	boxCollider.x = position.x;
	boxCollider.y = position.y;
	boxCollider.w = rect.w;
	boxCollider.h = rect.h;
	return true;
}

UpdateStatus Bullet::Update(float delta_time)
{
	if (active)
	{
		position.y -= speed * delta_time;

		boxCollider.x = position.x;
		boxCollider.y = position.y;

		// Draw box collider
		SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(&App->renderer->GetRenderer(), &boxCollider);

		App->renderer->Draw(texture, position, &rect);
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
