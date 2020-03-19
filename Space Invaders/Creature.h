#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "Entity.h"

class Creature : public Entity
{
public:
	Creature() {}
	Creature(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed);
	Creature(SDL_Texture* texture, Animation animation, SDL_Rect rect, fPoint position, int health, int damage, float speed);

	virtual UpdateStatus Update(float delta_time) = 0;
	void UpdateBoxCollider();
	int GetDamage() const;


protected:
	int damage;
	float speed;
};

#endif // _CREATURE_H_
