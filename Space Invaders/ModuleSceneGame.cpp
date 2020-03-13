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
}

ModuleSceneGame::~ModuleSceneGame()
{
	delete player;
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	player->Start();

	graphics = App->textures->LoadImage("Game/Background/background.jpg");

	return true;
}

UpdateStatus ModuleSceneGame::Update()
{
	App->renderer->Draw(graphics, fPoint::Zero(), &background, LAYER_BACK);

	player->Update();

	return UpdateStatus::CONTINUE;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");

	player->CleanUp();

	App->textures->Unload(graphics);

	return true;
}
