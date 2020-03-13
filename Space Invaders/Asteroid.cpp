#include "Asteroid.h"

Asteroid::Asteroid()
{
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
	return UpdateStatus::CONTINUE;
}

bool Asteroid::CleanUp()
{
	return true;
}
