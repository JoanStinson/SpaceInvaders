#include "Asteroid.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Asteroid::Asteroid()
{
	rect = { 0, 0, 102, 102 };
	tag = Tag::ASTEROID;
}

Asteroid::~Asteroid()
{
}

bool Asteroid::Start()
{
	box_collider.x = position.x;
	box_collider.y = position.y;
	box_collider.w = rect.w;
	box_collider.h = rect.h;
	return true;
}

UpdateStatus Asteroid::Update(float delta_time)
{
	// Draw box collider
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &box_collider);

	App->renderer->Draw(texture, position, &rect);

	return UpdateStatus::CONTINUE;
}

bool Asteroid::CleanUp()
{
	return true;
}
