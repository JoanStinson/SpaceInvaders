#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Bullet.h"

#include <vector>

struct SDL_Texture;
struct SDL_Rect;

#define RIGHT_LIMIT 72
#define LEFT_LIMIT 11
#define BOTTOM_LIMIT 204
#define BOUNCE_LIMIT 4 // default = 2

class Enemy : public Creature
{
public:
	Enemy();
	Enemy(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed);
	~Enemy();

	UpdateStatus Update(float delta_time) override;

	void Draw();
	void Move(iPoint position);

private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;

	Uint8 bounces_count = 0;
	bool jump_frame = false;
};

#endif // _ENEMY_H_
