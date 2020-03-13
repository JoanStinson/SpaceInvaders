#include "ModuleSceneGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"

#include <SDL.h>
#include <string>

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled)
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	player = new Player();
	AddEntity(player);


}

ModuleSceneGame::~ModuleSceneGame()
{
	delete player;
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	bool ret = true;

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	graphics = App->textures->LoadImage("Game/Background/background.jpg");

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	App->renderer->Draw(graphics, fPoint::Zero(), &background, LAYER_BACK);

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
