#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleRender.h"

#include <math.h>
#include <SDL.h>

ModuleFadeToBlack::ModuleFadeToBlack(bool start_enabled) : Module(start_enabled)
{
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{
}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(&App->renderer->GetRenderer(), SDL_BLENDMODE_BLEND);
	return true;
}

UpdateStatus ModuleFadeToBlack::Update()
{
	if (start_time > 0)
	{
		Uint32 now = SDL_GetTicks() - start_time;
		float normalized = (float)now / (float)total_time;

		if (normalized > 1.0F)
			normalized = 1.0F;

		if (fading_in == false)
			normalized = 1.0F - normalized;

		// Draw a screen-size black rectangle with alpha
		SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 0, 0, (Uint8)(normalized * 255.0F));
		SDL_RenderFillRect(&App->renderer->GetRenderer(), NULL);

		if (module_off == nullptr && module_on != nullptr)
		{
			module_on->Enable();
			module_on = nullptr;
		}

		if (now >= total_time)
		{
			if (fading_in == true)
			{
				if (module_off != nullptr)
					module_off->Disable();
				module_on->Enable();

				total_time += total_time;
				start_time = SDL_GetTicks();
				fading_in = false;
			}
			else
			{
				start_time = 0;
			}
		}
	}

	return UpdateStatus::CONTINUE;
}

void ModuleFadeToBlack::FadeToBlack(Module* module_on, Module* module_off, float time)
{
	fading_in = (module_off != nullptr) ? true : false;
	start_time = SDL_GetTicks();
	total_time = (Uint32)(time * 0.5F * 1000.0F);

	this->module_on = module_on;
	this->module_off = module_off;
}

bool ModuleFadeToBlack::isFading() const
{
	return start_time > 0;
}
