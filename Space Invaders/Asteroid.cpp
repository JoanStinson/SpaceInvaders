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
	return true;
}

UpdateStatus Asteroid::Update(float delta_time)
{
	App->renderer->Draw(texture, position, &rect, LAYER_FRONT);

	return UpdateStatus::CONTINUE;
}

bool Asteroid::CleanUp()
{
	return true;
}
