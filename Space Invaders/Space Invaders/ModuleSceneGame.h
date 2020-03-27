#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_

#include "Module.h"
#include "Player.h"
#include "Clock.h"
#include "EnemyGrid.h"
#include "Button.h"

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
	const std::list<Entity*>& GetEntities() const;

	void PlayGameOverSound() const;
	void NextEnemyWave();

private:
	UpdateStatus RunGame();
	UpdateStatus ShowGameOver();

public:
	int score = 0;
	int hiscore = 0;
	bool game_over = false;
	bool next_wave = false;

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

	SDL_Texture* texture_buttons = nullptr;
	Button buttons[2];

	unsigned int sfx_hover;
	unsigned int sfx_pressed;

	Text* game_over_title = nullptr;
	unsigned int sfx_game_over;
};

#endif // _MODULESCENEGAME_H_