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
	void CheckCollisions();

private:
	Entity* owner = nullptr;

	const int TOP_LIMIT = rect.w + 70;
	const int BOTTOM_LIMIT = SCREEN_HEIGHT - rect.w;
};

#endif // _BULLET_H