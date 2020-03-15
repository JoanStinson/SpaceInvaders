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

	void Move();

private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;

	Uint8 direction = -1;
};

#endif // _ENEMY_H_
