#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_

#include "Module.h"
#include "Animation.h"
#include "SDL_Button.h"
#include "Player.h"
#include "Clock.h"

#include <list>

struct SDL_Texture;
struct SDL_Rect;
struct Text;
enum class MouseMove;

class ModuleSceneGame : public Module
{
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

public:
	void AddEntity(Entity* entity);

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;

	Player* player = nullptr;
	std::list<Entity*> entities;
	//list<Entity*> walls;

	Clock clock;
};

#endif // _MODULESCENEGAME_H_