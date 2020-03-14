#include "Asteroid.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

Asteroid::Asteroid()
{
	rect = { 0, 0, 102, 102 };
}

Asteroid::~Asteroid()
{
}

bool Asteroid::Start()
{
	boxCollider.x = position.x;
	boxCollider.y = position.y;
	boxCollider.w = rect.w;
	boxCollider.h = rect.h;
	return true;
}

UpdateStatus Asteroid::Update(float delta_time)
{
	// Draw box collider
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &boxCollider);

	App->renderer->Draw(texture, position, &rect);

	return UpdateStatus::CONTINUE;
}

bool Asteroid::CleanUp()
{
	return true;
}
