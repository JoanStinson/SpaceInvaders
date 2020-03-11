#include "ModuleSceneMenu.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"

#include <SDL.h>

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneMenu::~ModuleSceneMenu()
{
}

bool ModuleSceneMenu::Start()
{
	LOG("Loading intro scene");
	return true;
}

UpdateStatus ModuleSceneMenu::Update()
{
	return UpdateStatus::CONTINUE;
}

bool ModuleSceneMenu::CleanUp()
{
	LOG("Unloading intro scene");
	return true;
}
