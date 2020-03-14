#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_

#include "Module.h"
#include "Player.h"
#include "Clock.h"

#include <list>

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

public:
	void AddEntity(Entity* entity);
	const std::list<Entity*>& GetEntities() const;

private:
	Player* player = nullptr;
	std::list<Entity*> entities;

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;

	Clock clock;
};

#endif // _MODULESCENEGAME_H_