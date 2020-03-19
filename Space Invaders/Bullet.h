#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(SDL_Rect rect, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed, Entity* owner);
	~Bullet();

	UpdateStatus Update(float delta_time) override;

private:
	Entity* owner = nullptr;
};

#endif // _BULLET_H