#include "EnemyGrid.h"

#include "Application.h"
#include "ModuleRender.h"

#include "SDL_render.h"
#include <functional>

EnemyGrid::EnemyGrid()
{
}

EnemyGrid::EnemyGrid(Uint8 rows, Uint8 cols) : rows(rows), cols(cols), current_row(rows - 1), grid_rect(SDL_Rect{ 0, 0, 0, 0 })
{
	grid.reserve(rows);

	row_rects.reserve(rows);

	for (int i = 0; i < rows; ++i)
	{
		row_rects.push_back(SDL_Rect{ 0, 0, 0, 0 });
	}
}

EnemyGrid::~EnemyGrid()
{
}

UpdateStatus EnemyGrid::Update(float delta_time)
{
	clock.Tick();

	//UpdateEnemies(delta_time);

	DrawGridRects();

	clock.Invoke(0.3f, std::bind(&EnemyGrid::MoveEnemyRow, this));

	return UpdateStatus::CONTINUE;
}

void EnemyGrid::CreateGridRects()
{
	// Calculate rects
	for (int i = 0; i < rows; ++i)
	{
		SDL_Rect row_rect{ 0, 0, 0, };

		for (int j = 0; j < cols; ++j)
		{
			SDL_UnionRect(&row_rect, &grid[i][j]->GetBoxCollider(), &row_rect);
		}

		row_rects[i] = row_rect;
	}

	grid_rect = SDL_Rect{ 0, 0, 0, 0 };
}

void EnemyGrid::UpdateEnemies(float delta_time)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (grid[i][j]->enabled)
				grid[i][j]->Update(delta_time);
		}
	}
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
	LOG("%d", grid_rect.y);
	for (int j = 0; j < cols; ++j)
	{
		grid[current_row][j]->Move(iPoint(row_rects[current_row].x, grid_rect.y));
	}

	current_row--;

	speed += 0.15f; // each row has different speed

	if (current_row < 0)
	{
		current_row = rows - 1;
		speed = init_speed;
	}

	CreateGridRects(); // update only after moving
}
