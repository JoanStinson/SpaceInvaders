#include "EnemyGrid.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL_render.h>
#include <functional>
#include <stdlib.h>  

EnemyGrid::EnemyGrid()
{
}

EnemyGrid::EnemyGrid(int rows, int cols) : rows(rows), cols(cols), current_row(rows - 1), grid_rect(SDL_Rect{ 0, 0, 0, 0 })
{
	grid.reserve(rows);

	row_rects.reserve(rows);

	for (int i = 0; i < rows; ++i)
		row_rects.push_back(SDL_Rect{ 0, 0, 0, 0 });
}

EnemyGrid::~EnemyGrid()
{
	// enemy grid is cleared on ModuleSceneGame destructor
}

UpdateStatus EnemyGrid::Update(float delta_time)
{
	clock_move.Tick();
	clock_shoot.Tick();

	DrawGridRects();

	clock_move.Invoke(0.3f, std::bind(&EnemyGrid::MoveEnemyRow, this));

	clock_shoot.Invoke(0.5f, std::bind(&EnemyGrid::ShootBullet, this));

	return UpdateStatus::CONTINUE;
}

void EnemyGrid::CreateGridRects()
{
	for (int i = 0; i < rows; ++i)
	{
		SDL_Rect row_rect{ 0, 0, 0, };

		for (int j = 0; j < cols; ++j)
			SDL_UnionRect(&row_rect, &grid[i][j]->GetRectCollider(), &row_rect);

		row_rects[i] = row_rect;
	}

	grid_rect = SDL_Rect{ 0, 0, 0, 0 };
}

void EnemyGrid::DrawGridRects()
{
	if (!Entity::debug_draw)
	{
		for (int i = 0; i < row_rects.size(); ++i)
			SDL_UnionRect(&grid_rect, &row_rects[i], &grid_rect);

		return;
	}

	// Draw row rects
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < row_rects.size(); ++i)
	{
		SDL_RenderDrawRect(&App->renderer->GetRenderer(), &row_rects[i]);
		SDL_UnionRect(&grid_rect, &row_rects[i], &grid_rect);
	}

	// Draw grid rect
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &grid_rect);
}

void EnemyGrid::MoveEnemyRow()
{
	for (int j = 0; j < cols; ++j)
		grid[current_row][j]->Move(iPoint(row_rects[current_row].x, grid_rect.y));

	current_row--;

	speed += 0.15f; // each row has different speed

	if (current_row < 0)
	{
		current_row = rows - 1;
		speed = init_speed;
	}

	CreateGridRects(); // update only after moving
}

void EnemyGrid::ShootBullet()
{
	std::vector<Enemy*> enemies_that_can_shoot;
	std::vector<bool> has_enemy_in_col;
	has_enemy_in_col.reserve(cols);
	for (int i = 0; i < cols; ++i)
		has_enemy_in_col.push_back(false);

	// Iterate grid from bottom->top, left<-right
	for (int i = rows - 1; i >= 0; --i)
	{
		for (int j = cols - 1; j >= 0; --j)
		{
			if (!grid[i][j]->enabled || !grid[i][j]->alive || has_enemy_in_col[j]) continue;

			// If it can shoot save it, get the most bottom enemy of each col
			if ((grid[i][j]->GetPosition().x >= 55 && grid[i][j]->GetPosition().x <= 100) ||
				(grid[i][j]->GetPosition().x >= 180 && grid[i][j]->GetPosition().x <= 225) ||
				(grid[i][j]->GetPosition().x >= 305 && grid[i][j]->GetPosition().x <= 350))
			{
				enemies_that_can_shoot.push_back(grid[i][j]);
				has_enemy_in_col[j] = true;
			}
		}
	}

	// From the enemies that can shoot, choose a random one
	if (enemies_that_can_shoot.size() > 0)
	{
		int random_index = rand() % enemies_that_can_shoot.size();
		enemies_that_can_shoot[random_index]->Shoot();
	}
}
