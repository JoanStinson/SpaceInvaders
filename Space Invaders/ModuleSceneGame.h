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
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;

public:
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	const std::list<Entity*>& GetEntities() const;

private:
	Player* player = nullptr;
	EnemyGrid* enemy_grid = nullptr;
	std::list<Entity*> entities;

private:
	Clock clock;

	SDL_Texture* texture_background = nullptr;
	SDL_Rect rect_background;

	Text* lives_title = nullptr;
	Text* score_title = nullptr;
	Text* hiscore_title = nullptr;

	Text* lives_value = nullptr;
	Text* score_value = nullptr;
	Text* hiscore_value = nullptr;

	const int ROWS = 3;
	const int COLS = 6;
};

#endif // _MODULESCENEGAME_H_