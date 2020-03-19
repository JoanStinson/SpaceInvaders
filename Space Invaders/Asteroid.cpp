#include "Asteroid.h"

#include "Application.h"
#include "ModuleRender.h"

Asteroid::Asteroid(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health) :
	Entity(texture, rect, position, health)
{
	type = Type::ASTEROID;
}

Asteroid::~Asteroid()
{
}

UpdateStatus Asteroid::Update(float delta_time)
{
	//Entity::DrawEntity();
	//Entity::DrawAnimation();


	if (health < 1)
	{
		

		if (!die_animation.HasAnimationEnded())
		{
			App->renderer->Draw(die_texture, position, &(die_animation.GetCurrentFrameOnce()));
			
		}
		else
		{
			enabled = false;
		}
	}
	else
	{
		Entity::DrawEntity();
	}


	return UpdateStatus::CONTINUE;
}
