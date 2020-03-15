#include "Asteroid.h"

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
	Entity::DrawEntity();
	return UpdateStatus::CONTINUE;
}
