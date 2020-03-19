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
//#include "Animation.h"

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

	// Asteroids
	SDL_Texture* asteroid_texture = App->textures->LoadImage("Sprites/asteroid.png");
	float asteroid_y = SCREEN_HEIGHT - (64 * 3) + 12;
	float asteroid_x = 15;
	float offset = 64;
	fPoint asteroid_positions[]{ fPoint{asteroid_x+0, asteroid_y}, fPoint{asteroid_x+(offset *2), asteroid_y}, fPoint{asteroid_x+(offset *4), asteroid_y}, fPoint{asteroid_x+(offset *6), asteroid_y} };

	for (int i = 0; i < sizeof(asteroid_positions) / sizeof(asteroid_positions[0]); ++i)
		AddEntity(new Asteroid(asteroid_texture, SDL_Rect{ 0, 0, 64, 64 }, asteroid_positions[i], 3));

	// Enemies
	enemy_grid = EnemyGrid(rows, cols);
	SDL_Texture* enemy_texture = App->textures->LoadImage("Sprites/spaceship_enemy.png");
	Animation enemy_animation(8, 0.8f);
	for (int i = 0; i < 8; ++i)
	{
		int pos_x = i * 64;
		enemy_animation.AddFrame({ pos_x, 0, 64, 64 });
	}
	for (int i = 0; i < rows; ++i)
	{
		std::vector<Enemy*> enemy_row;

		for (int j = 0; j < cols; ++j)
		{
			fPoint position = { float((64 * j) + 12), float((64 * i) + (64*2)) }; // calculation to have enemies aligned in grid
			Enemy* enemy = new Enemy(enemy_texture, enemy_animation, SDL_Rect{ 0, 0, 64, 64 }, position, 3, 1, 10.f);
			enemy_row.push_back(enemy);
			AddEntity(enemy);
		}

		enemy_grid.grid.push_back(enemy_row);
	}

	enemy_grid.CreateGridRects();

	// Player
	player_animation = Animation(8, 0.8f);
	for (int i = 0; i < 8; ++i)
	{
		int pos_x = i * 64;
		player_animation.AddFrame({pos_x, 0, 64, 64});
	}
	player_texture = App->textures->LoadImage("Sprites/spaceship.png");

	player = new Player(App->textures->LoadImage("Sprites/spaceship.png"), player_animation, SDL_Rect{ 0, 0, 64, 64 }, fPoint{ (SCREEN_WIDTH / 2)-(64/2), SCREEN_HEIGHT - 96 }, 3, 1, 0.5f);
	AddEntity(player);

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	// Draw background
	App->renderer->Draw(texture, fPoint(), &background);


	//App->renderer->Draw(player_texture, fPoint{ 0, 100 }, &(player_animation.GetCurrentFrame()));

	// Update enemies
	enemy_grid.Update((float)clock.delta_time);

	// Update entities
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
