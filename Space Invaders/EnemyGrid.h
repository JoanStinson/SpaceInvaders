#ifndef _ENEMYGRID_H_
#define _ENEMYGRID_H_

#include "Enemy.h"
#include "Clock.h"
#include <vector>

struct SDL_Rect;

class EnemyGrid : public Entity
{
public:
	EnemyGrid();
	EnemyGrid(Uint8 rows, Uint8 cols);
	~EnemyGrid();

	UpdateStatus Update(float delta_time) override;
	void CreateGridRects();

private:
	void UpdateEnemies(float delta_time);
	void DrawGridRects();
	void MoveEnemyRow();

public:
	Uint8 rows;
	Uint8 cols;

	std::vector<std::vector<Enemy*>> grid;

	std::vector<SDL_Rect> row_rects;
	SDL_Rect grid_rect;

	Clock clock;

	int current_row;
	float speed = 0.5f;
	float init_speed = speed;
};

#endif // _ENEMYGRID_H_
