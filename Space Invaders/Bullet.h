#ifndef _BULLET_H_
#define _BULLET_H_

#include "Creature.h"

class Bullet : public Creature
{
public:
	Bullet(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed);
	~Bullet();

	UpdateStatus Update(float delta_time) override;
};

#endif // _BULLET_H