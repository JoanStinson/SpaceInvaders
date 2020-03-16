#ifndef _ENEMYGRID_H_
#define _ENEMYGRID_H_

#include "Enemy.h"
#include "Clock.h"
#include <vector>

struct SDL_Rect;

class EnemyGrid
{
public:
	EnemyGrid();
	EnemyGrid(Uint8 rows, Uint8 cols);
	~EnemyGrid();

	void Update(float delta_time);
	void CreateGridRects();

private:
	void DrawEnemies();
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
