#include "ModuleSceneGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "Asteroid.h"

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

	graphics = App->textures->LoadImage("Game/Background/background.jpg");

	player = new Player();
	AddEntity(player);

	Asteroid* asteroid = new Asteroid();
	SDL_Texture* asteroidTexture = App->textures->LoadImage("Game/Aestroids/aestroid_brown.png");
	asteroid->SetTexture(asteroidTexture);
	asteroid->SetPosition(fPoint{ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3 });
	asteroid->Start();
	AddEntity(asteroid);

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	App->renderer->Draw(graphics, fPoint::Zero(), &background);

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Update((float)clock.delta_time);

	return ret;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");

	bool ret = true;

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->CleanUp();

	return ret;
}

void ModuleSceneGame::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}
