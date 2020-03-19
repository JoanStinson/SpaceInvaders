#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Bullet.h"

#include <vector>

struct SDL_Texture;
struct SDL_Rect;

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	~Enemy();

	UpdateStatus Update(float delta_time) override;
	void Move(iPoint position);

private:
	std::vector<Bullet*> pooled_bullets;

	int bounces_count = 0;
	bool jump_frame = false;

	const int RIGHT_LIMIT = 74;
	const int LEFT_LIMIT = 24;
	const int BOTTOM_LIMIT = 289;
	const int BOUNCE_LIMIT = 0; 
};

#endif // _ENEMY_H_
