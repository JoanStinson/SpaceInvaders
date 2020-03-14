#include "Bullet.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"

#include <SDL.h>

Bullet::Bullet()
{
	box_collider = rect = { 0, 0, 26, 26 };

	active = false;
	speed = 0.1f;

	tag = Tag::BULLET;
}

Bullet::~Bullet()
{
}

bool Bullet::Start()
{
	LOG("Loading bullet");
	box_collider.x = position.x;
	box_collider.y = position.y;
	box_collider.w = rect.w;
	box_collider.h = rect.h;
	return true;
}

UpdateStatus Bullet::Update(float delta_time)
{
	if (active)
	{
		position.y -= speed * delta_time;

		box_collider.x = position.x;
		box_collider.y = position.y;

		// Draw box collider
		SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(&App->renderer->GetRenderer(), &box_collider);

		App->renderer->Draw(texture, position, &rect);

		// Collisions
		auto entities = App->sceneGame->GetEntities();//Todo hacerlo en el start

		for (auto& entity : entities)
		{
			if (!entity->IsEnabled) continue;

			if (entity->GetTag() == Tag::ASTEROID)
			{
				if (SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
				{
					active = false;
					break;
				}
			}
			//TODO if choca con el player, active = false y restarle vida al player
		}
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
