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

ModuleSceneGame::ModuleSceneGame(bool start_enabled) 
	: Module(start_enabled), background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
{
}

ModuleSceneGame::~ModuleSceneGame()
{
	for (std::list<Entity*>::iterator it = Entity::entities.begin(); it != Entity::entities.end(); ++it)
		delete (*it);
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	bool ret = true;

	// Background
	texture = App->textures->LoadImage("Game/Background/background.jpg");

	// Asteroids
	SDL_Texture* asteroid_texture = App->textures->LoadImage("Game/Aestroids/aestroid_brown.png");
	fPoint asteroid_positions[]{ fPoint{100, 350}, fPoint{200, 350}, fPoint{300, 350}, fPoint{400, 350} };

	for (int i = 0; i < sizeof(asteroid_positions) / sizeof(asteroid_positions[0]); ++i)
		Entity::AddEntity(new Asteroid(asteroid_texture, SDL_Rect{ 0, 0, 102, 102 }, asteroid_positions[i], 3));

	// Enemies
	Enemy* enemy = new Enemy(App->textures->LoadImage("Game/Enemy/spaceship_enemy_red.png"), SDL_Rect{ 0, 0, 102, 102 }, fPoint{ 100, 0 }, 3, 1, 30.1f);
	Entity::AddEntity(enemy);

	// Player
	player = new Player(App->textures->LoadImage("Game/Player/spaceship.png"), SDL_Rect{ 0, 0, 102, 102 }, fPoint{ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 140 }, 3, 1, 0.5f);
	Entity::AddEntity(player);

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	App->clock.Tick();

	App->renderer->Draw(texture, fPoint(), &background);

	for (std::list<Entity*>::iterator it = Entity::entities.begin(); it != Entity::entities.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->enabled)
			ret = (*it)->Update((float)App->clock.delta_time);

	if (App->input->GetKeyDown(SDL_SCANCODE_D))
		Entity::debug_draw = !Entity::debug_draw;

	return ret;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");

	bool ret = true;

	return ret;
}
