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
}

ModuleSceneGame::~ModuleSceneGame()
{
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	graphics = App->textures->LoadImage("Game/Background/background.jpg");

	return true;
}

UpdateStatus ModuleSceneGame::Update()
{
	App->renderer->Blit(graphics, 0, 0, &background, LAYER_BACK);

	return UpdateStatus::CONTINUE;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");

	App->textures->Unload(graphics);

	return true;
}
