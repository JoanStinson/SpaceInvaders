#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_

#include "Module.h"
#include "Player.h"
#include "Clock.h"

struct SDL_Texture;
struct SDL_Rect;
struct Text;

class ModuleSceneGame : public Module
{
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
	Clock clock;
private:
	Player* player = nullptr;

	SDL_Texture* texture = nullptr;
	SDL_Rect background;


};

#endif // _MODULESCENEGAME_H_