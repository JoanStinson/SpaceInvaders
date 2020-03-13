#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;

class Player
{
public:
	Player();
	~Player();

	bool Start();
	UpdateStatus Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect spaceship;

	fPoint position;
	const float speed = 350.0f / FPS;
};

#endif // _PLAYER_H_
