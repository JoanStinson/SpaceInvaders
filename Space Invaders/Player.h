#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Creature.h"

struct SDL_Texture;
struct SDL_Rect;

class Player : public Creature
{
public:
	Player();
	Player(fPoint position, float speed);
	~Player();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect spaceship;
};

#endif // _PLAYER_H_
