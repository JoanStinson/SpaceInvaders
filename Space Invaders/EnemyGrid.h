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

	void MoveEnemies();

public:
	std::vector<std::vector<Enemy*>> grid;
	std::vector<SDL_Rect> row_rects;
	SDL_Rect final_rect;
	Uint8 rows;
	Uint8 cols;

	Clock clock;

	int current_row = 0;

	float speed = 0.5f;
	float current_pos;
	float posy;
};

#endif // _ENEMYGRID_H_
