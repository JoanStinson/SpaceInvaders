#include "ModuleSceneGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Animation.h"

#include <sstream>
#include <iomanip>

ModuleSceneGame::ModuleSceneGame(bool start_enabled)
	: Module(start_enabled), background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
{
}

ModuleSceneGame::~ModuleSceneGame()
{
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete (*it);
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	bool ret = true;

	// Background
	texture = App->textures->LoadImage("Sprites/background.jpg");

	// Generic
	SDL_Texture* entity_texture_death = App->textures->LoadImage("Sprites/galaxy.png");
	Animation entity_animation_death(17, 64, 0.8f);

	// Asteroids
	SDL_Texture* asteroid_texture = App->textures->LoadImage("Sprites/asteroid.png");

	float asteroid_position_y = SCREEN_HEIGHT - (64 * 3) + 20;
	float asteroid_position_x = 15;
	float asteroid_offset_x = 64;

	fPoint asteroid_positions[]
	{
		fPoint{asteroid_position_x, asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 2), asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 4), asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 6), asteroid_position_y}
	};

	for (int i = 0; i < sizeof(asteroid_positions) / sizeof(asteroid_positions[0]); ++i)
		AddEntity(new Asteroid({ 0, 0, 64, 64 }, asteroid_texture, entity_texture_death, entity_animation_death, asteroid_positions[i], 4));

	// Enemies
	SDL_Texture* enemy_texture = App->textures->LoadImage("Sprites/spaceship_enemy.png");
	Animation enemy_animation(8, 64, 0.4f);
	enemy_grid = new EnemyGrid(ROWS, COLS);

	for (int i = 0; i < ROWS; ++i)
	{
		std::vector<Enemy*> enemy_row;

		for (int j = 0; j < COLS; ++j)
		{
			fPoint enemy_position =
			{
				(float)(64 * j) + 25,
				(float)(64 * i) + (48 * 2)
			};

			Enemy* enemy = new Enemy({ 0, 0, 64, 64 }, enemy_texture, enemy_animation, entity_texture_death, entity_animation_death, enemy_position, 1, 1, 10.f);
			enemy_row.push_back(enemy);
			AddEntity(enemy);
		}

		enemy_grid->grid.push_back(enemy_row);
	}

	enemy_grid->CreateGridRects();
	AddEntity(enemy_grid);

	// Player
	SDL_Texture* player_texture = App->textures->LoadImage("Sprites/spaceship.png");
	Animation player_animation(8, 64);

	fPoint player_position
	{
		(SCREEN_WIDTH / 2) - 32,
		SCREEN_HEIGHT - 96
	};

	player = new Player({ 0, 0, 64, 64 }, player_texture, player_animation, entity_texture_death, entity_animation_death, player_position, 3, 1, 0.5f);
	AddEntity(player);

	// Static text
	lives_title = new Text(App->textures->LoadText("LIVES"));
	score_title = new Text(App->textures->LoadText("SCORE"));
	hiscore_title = new Text(App->textures->LoadText("HI-SCORE"));

	// Dynamic text
	lives_value = new Text(App->textures->LoadText(PadZerosLeft(player->life_points).c_str()));
	score_value = new Text(App->textures->LoadText(PadZerosLeft(player->score).c_str()));
	hiscore_value = new Text(App->textures->LoadText(PadZerosLeft(player->high_score).c_str()));

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	// Draw background
	App->renderer->Draw(texture, fPoint(), &background);

	// Draw static text
	App->renderer->Draw(lives_title->texture, fPoint{ 30, 15 }, &lives_title->rect);
	App->renderer->Draw(score_title->texture, fPoint{ 170, 15 }, &score_title->rect);
	App->renderer->Draw(hiscore_title->texture, fPoint{ 310, 15 }, &hiscore_title->rect);

	// Draw dynamic text
	lives_value->Update(App->textures->LoadText(PadZerosLeft(player->life_points).c_str()));
	score_value->Update(App->textures->LoadText(PadZerosLeft(player->score).c_str()));
	hiscore_value->Update(App->textures->LoadText(PadZerosLeft(player->high_score).c_str()));

	App->renderer->Draw(lives_value->texture, fPoint{ 34, 55 }, &lives_value->rect);
	App->renderer->Draw(score_value->texture, fPoint{ 181, 55 }, &score_value->rect);
	App->renderer->Draw(hiscore_value->texture, fPoint{ 340, 55 }, &hiscore_value->rect);

	// Draw entities
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->enabled)
			ret = (*it)->Update((float)clock.delta_time);

	// Toggle box colliders
	if (App->input->GetKeyDown(SDL_SCANCODE_D))
		Entity::debug_draw = !Entity::debug_draw;

	//TODO check if player win or game over
	//if (player->win)
	//{
	//	//todo
	//}

	return ret;
}

UpdateStatus ModuleSceneGame::PostUpdate()
{
	App->textures->Unload(lives_value->texture);
	App->textures->Unload(score_value->texture);
	App->textures->Unload(hiscore_value->texture);
	return UpdateStatus::CONTINUE;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");

	bool ret = true;

	return ret;
}

void ModuleSceneGame::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void ModuleSceneGame::RemoveEntity(Entity* entity)
{
	entities.remove(entity);
	delete entity;
}

const std::list<Entity*>& ModuleSceneGame::GetEntities() const
{
	return entities;
}

std::string ModuleSceneGame::PadZerosLeft(int value) const
{
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << value;
	std::string s = ss.str();
	return s;
}
