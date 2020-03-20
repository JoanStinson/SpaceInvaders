#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage = 0, float move_speed = 0.f);
	~Asteroid();

	UpdateStatus Update(float delta_time) override;
};

#endif // _ASTEROID_H_
