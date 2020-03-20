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
	EnemyGrid(int rows, int cols);
	~EnemyGrid();

	UpdateStatus Update(float delta_time);
	void CreateGridRects();

private:
	void DrawGridRects();
	void MoveEnemyRow();
	void ShootBullet();

public:
	int rows;
	int cols;

	std::vector<std::vector<Enemy*>> grid;

	std::vector<SDL_Rect> row_rects;
	SDL_Rect grid_rect;

	Clock clock_move;
	Clock clock_shoot;

	int current_row;
	float speed = 0.5f;
	float init_speed = speed;

	unsigned int sfx_move;
};

#endif // _ENEMYGRID_H_
