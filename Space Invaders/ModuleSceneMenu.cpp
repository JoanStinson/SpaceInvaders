#include "ModuleSceneMenu.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"

#include <SDL.h>

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled)
	: Module(start_enabled), rect_background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }), rect_logo(SDL_Rect{ 0, 0, 420, 176 })
{
}

ModuleSceneMenu::~ModuleSceneMenu()
{
}

bool ModuleSceneMenu::Start()
{
	LOG("Loading intro scene");
	bool ret = true;

	texture_background = App->textures->LoadImage("Sprites/background.jpg");
	texture_logo = App->textures->LoadImage("Sprites/logo.png");

	return ret;
}

UpdateStatus ModuleSceneMenu::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	App->renderer->Draw(texture_background, fPoint(), &rect_background);
	App->renderer->Draw(texture_logo, fPoint{ (float)(SCREEN_WIDTH / 2) - (rect_logo.w / 2) - 2, 50 }, &rect_logo);

	return ret;
}

bool ModuleSceneMenu::CleanUp()
{
	LOG("Unloading intro scene");
	bool ret = true;

	return ret;
}
