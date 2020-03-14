#include "ModuleSceneGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "Asteroid.h"
#include "Entity.h"

#include <SDL.h>
#include <string>

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled)
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//TODO remember that cant use modules until Start, because they are not initialized before
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

	texture = App->textures->LoadImage("Game/Background/background.jpg");

	player = new Player(App->textures->LoadImage("Game/Player/spaceship.png"), SDL_Rect{ 0, 0, 102, 102 }, fPoint{ SCREEN_WIDTH/2, SCREEN_HEIGHT-140}, 3, 1, 0.5f);
	AddEntity(player);

	Asteroid* asteroid = new Asteroid(App->textures->LoadImage("Game/Aestroids/aestroid_brown.png"), SDL_Rect{ 0, 0, 102, 102 }, fPoint{ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3 }, 3);
	AddEntity(asteroid);

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	App->renderer->Draw(texture, fPoint::Zero(), &background);

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsActive())
			ret = (*it)->Update((float)clock.delta_time);

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
