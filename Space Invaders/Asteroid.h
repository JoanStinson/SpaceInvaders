#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
public:
	Asteroid(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health);
	~Asteroid();

	UpdateStatus Update(float delta_time) override;
};

#endif // _ASTEROID_H_
