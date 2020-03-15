#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Bullet.h"

#include <vector>

struct SDL_Texture;
struct SDL_Rect;

class Enemy : public Creature
{
public:
	Enemy(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed);
	~Enemy();

	UpdateStatus Update(float delta_time) override;

private:
	void Move();

private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;

	const int RIGHT_LIMIT = SCREEN_WIDTH - rect.w;
	const int LEFT_LIMIT = 0;
	const int BOTTOM_LIMIT = SCREEN_HEIGHT - (rect.h * 4);
	const int BOUNCE_LIMIT = 0;

	Uint8 bounces_count = 0;
	bool jump_frame = false;
};

#endif // _ENEMY_H_
