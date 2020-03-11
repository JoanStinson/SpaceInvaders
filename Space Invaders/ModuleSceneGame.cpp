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
}

ModuleSceneGame::~ModuleSceneGame()
{
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");
	return true;
}

UpdateStatus ModuleSceneGame::Update()
{
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleSceneGame::PostUpdate()
{
	return UpdateStatus::CONTINUE;
}

bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading game scene");
	return true;
}
