#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bullet.h"

#include <vector>

#define MAX_BULLETS 50

struct SDL_Texture;
struct SDL_Button_t;

class Player : public Creature
{
public:
	Player();
	Player(fPoint position, float speed);
	~Player();

	bool Start() override;
	UpdateStatus Update(float delta_time) override;
	bool CleanUp() override;

private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;

	SDL_Button_t* retryButton = nullptr;

	SDL_Texture* buttonTexture = nullptr;
};

#endif // _PLAYER_H_
