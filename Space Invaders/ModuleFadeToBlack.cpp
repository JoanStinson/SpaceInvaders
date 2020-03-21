#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL.h>
#include <math.h>

ModuleFadeToBlack::ModuleFadeToBlack(bool start_enabled) : Module(start_enabled)
{
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{
}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(&App->render->GetRenderer(), SDL_BLENDMODE_BLEND);
	return true;
}

UpdateStatus ModuleFadeToBlack::Update()
{
	if (start_time > 0)
	{
		Uint32 now = SDL_GetTicks() - start_time;
		float normalized = (float)now / (float)total_time;

		if (normalized > 1.f)
			normalized = 1.f;

		if (fading_in == false)
			normalized = 1.f - normalized;

		// Draw a screen-size black rectangle with alpha
		SDL_SetRenderDrawColor(&App->render->GetRenderer(), 0, 0, 0, (Uint8)(normalized * 255.f));
		SDL_RenderFillRect(&App->render->GetRenderer(), NULL);

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
	total_time = (Uint32)(time * 0.5f * 1000.f);

	this->module_on = module_on;
	this->module_off = module_off;
}

bool ModuleFadeToBlack::IsFading() const
{
	return start_time > 0;
}
