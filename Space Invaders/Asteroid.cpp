#include "Asteroid.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, rect_collider, texture, texture_death, animation_death, position, life_points, damage, move_speed)
{
	type = Type::ASTEROID;
}

Asteroid::~Asteroid()
{
}

UpdateStatus Asteroid::Update(float delta_time)
{
	if (DrawAnimationDeath(life_points < 1)) 
		return UpdateStatus::CONTINUE;

	Draw();

	return UpdateStatus::CONTINUE;
}

void Asteroid::OnDeath()
{
	enabled = false;
}
