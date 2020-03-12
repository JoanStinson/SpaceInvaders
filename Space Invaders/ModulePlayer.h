#ifndef _MODULEPLAYER_H_
#define _MODULEPLAYER_H_

#include "Module.h"

#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect spaceship;

	fPoint position;
	float speed = 350.0f / FPS;
	float currentTime;
};

#endif // _MODULEPLAYER_H_
