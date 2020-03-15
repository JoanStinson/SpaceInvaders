#include "EnemyGrid.h"

#include "Application.h"
#include "ModuleRender.h"

#include "SDL_render.h"
#include <functional>

EnemyGrid::EnemyGrid()
{
}

EnemyGrid::EnemyGrid(Uint8 rows, Uint8 cols) : rows(rows), cols(cols)
{
	//grid = (Enemy*) [rows]();

	//for (int i = 0; i < rows; ++i)
	//	grid[i] = new Enemy[cols]();

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

void EnemyGrid::Update(float delta_time)
{
	clock.Tick();



	for (int i = 0; i < rows; ++i)
	{
		SDL_Rect row_rect{ 0, 0, 0, };

		for (int j = 0; j < cols; ++j)
		{
			grid[i][j]->Draw();

			SDL_UnionRect(&row_rect, &grid[i][j]->GetBoxCollider(), &row_rect);
		}

		row_rects[i] = row_rect;
	}
	final_rect = SDL_Rect{ 0, 0, 0, 0 };
	for (int i = 0; i < row_rects.size(); ++i)
	{
		SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawRect(&App->renderer->GetRenderer(), &row_rects[i]);
		LOG("posx: %d\n", row_rects[i].x);
		SDL_UnionRect(&final_rect, &row_rects[i], &final_rect);
	}

	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &final_rect);

	current_pos = row_rects[current_row].x;
	posy = row_rects[current_row].y;
	LOG("%f", current_pos);
	//row_rects.clear();

	clock.Invoke(0.3f, std::bind(&EnemyGrid::MoveEnemies, this));
}

void EnemyGrid::MoveEnemies()
{

	for (int j = 0; j < cols; ++j)
	{
		grid[current_row][j]->Move(row_rects[current_row].x, final_rect.y);
	}


	current_row++;
	speed += 0.15f;
	if (current_row == rows)
	{
		current_row = 0;
		speed = 0.5f;
	}

	//row_rects.clear();
}
