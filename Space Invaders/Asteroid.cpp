#include "Asteroid.h"

#include "Application.h"
#include "ModuleRender.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(SDL_Rect rect, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, texture, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::ASTEROID;
}

Asteroid::~Asteroid()
{
}

UpdateStatus Asteroid::Update(float delta_time)
{
	if (life_points < 1)
	{
		if (!animation_death.HasAnimationEnded())
		{
			App->renderer->Draw(texture_death, position, &(animation_death.GetCurrentFrameOnce()));
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
