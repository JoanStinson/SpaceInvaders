#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_

#include "Module.h"
#include "Player.h"
#include "Clock.h"
#include "EnemyGrid.h"

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
	void RemoveEntity(Entity* entity);
	const std::list<Entity*>& GetEntities() const;

private:
	Player* player = nullptr;
	EnemyGrid enemy_grid;
	std::list<Entity*> entities;

private:
	Clock clock;

	int rows = 3;
	int cols = 4;
	int offset = 20;

	SDL_Texture* texture = nullptr;
	SDL_Rect background;
};

#endif // _MODULESCENEGAME_H_