#include "ModuleRender.h"

#include "Application.h"
#include "ModuleWindow.h"

#include <SDL_render.h>

ModuleRender::ModuleRender(bool start_enabled) : Module(start_enabled)
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

ModuleRender::~ModuleRender()
{
}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(&App->window->GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

UpdateStatus ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UpdateStatus::CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	// Destroy render
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::Draw(SDL_Texture* texture, fPoint position, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + position.x;
	rect.y = (int)(camera.y * speed) + position.y;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

SDL_Renderer& ModuleRender::GetRenderer() const
{
	return *renderer;
}
