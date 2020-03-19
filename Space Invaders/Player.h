#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bullet.h"

#include <vector>

class Player : public Entity
{
public:
	Player();
	Player(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	~Player();

	UpdateStatus Update(float delta_time) override;

public:
	int score = 0;
	int high_score = 0;

private:
	std::vector<Bullet*> pooled_bullets;

	const int MAX_BULLETS = 50;
	const int RIGHT_LIMIT = SCREEN_WIDTH - rect.w - 15;
	const int LEFT_LIMIT = 15;
};

#endif // _PLAYER_H_
