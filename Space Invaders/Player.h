#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bullet.h"

#include <vector>

#define MAX_BULLETS 50

struct SDL_Texture;
struct SDL_Rect;
struct SDL_Button_t;

class Player : public Creature
{
public:
	Player(SDL_Texture* texture, Animation animation, SDL_Rect rect, fPoint position, int health, int damage, float speed);
	~Player();

	UpdateStatus Update(float delta_time) override;

private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;
};

#endif // _PLAYER_H_
