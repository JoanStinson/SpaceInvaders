#include "ModuleSceneMenu.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGame.h"
#include "Utils.h"

#include <SDL.h>

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled) : 
	Module(start_enabled), rect_background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }), rect_logo(SDL_Rect{ 0, 0, 420, 176 })
{
	buttons[0].rect = { 0, 0, 256, 107 };
	buttons[0].rect_hover = { 256, 0, 256, 107 };
	buttons[0].position = fPoint{ (float)(SCREEN_WIDTH / 2) - (buttons[0].rect.w / 2) - 2, 300 };

	buttons[1].rect = { 512, 0, 256, 107 };
	buttons[1].rect_hover = { 768, 0, 256, 107 };
	buttons[1].position = fPoint{ (float)(SCREEN_WIDTH / 2) - (buttons[1].rect.w / 2) - 2, 425 };

	buttons[2].rect = { 1024, 0, 256, 107 };
	buttons[2].rect_hover = { 1280, 0, 256, 107 };
	buttons[2].position = fPoint{ (float)(SCREEN_WIDTH / 2) - (buttons[2].rect.w / 2) - 2, 550 };
}

ModuleSceneMenu::~ModuleSceneMenu()
{
}

bool ModuleSceneMenu::Start()
{
	LOG("Loading intro scene");
	bool ret = true;

	texture_background = App->texture->LoadTexture("Sprites/background.jpg");
	texture_logo = App->texture->LoadTexture("Sprites/logo.png");
	texture_buttons = App->texture->LoadTexture("Sprites/buttons.png");

	sfx_hover = App->audio->LoadSfx("Audio/Sfx/hover_button.wav");
	sfx_pressed = App->audio->LoadSfx("Audio/Sfx/click_button.wav");

	App->audio->PlayMusic("Audio/Music/main_theme.mpeg");

	return ret;
}

UpdateStatus ModuleSceneMenu::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	// Draw background and logo
	App->render->Draw(*texture_background, fPoint(), rect_background);
	App->render->Draw(*texture_logo, fPoint{ (float)(SCREEN_WIDTH / 2) - (rect_logo.w / 2) - 2, 60 }, rect_logo);

	iPoint mouse_pos = App->input->GetMousePosition();
	bool mouse_clicked = App->input->GetMouseButtonDown(1);

	// Draw buttons and handle hovering
	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i)
	{
		App->render->Draw(*texture_buttons, buttons[i].position, buttons[i].GetRect(mouse_pos));

		if (buttons[i].Hovered(mouse_pos) && !buttons[i].play_hover_audio)
		{
			App->audio->PlaySfx(sfx_hover);
			buttons[i].play_hover_audio = true;
		}
		else if (!buttons[i].Hovered(mouse_pos) && buttons[i].play_hover_audio)
		{
			buttons[i].play_hover_audio = false;
		}
	}

	// Button selection
	if (buttons[0].Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		App->audio->StopMusic();
		App->fade->FadeToBlack(App->scene_game.get(), App->scene_menu.get(), 3.f);
	}
	else if (buttons[1].Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		utils::OpenUrl("https://joangm.itch.io");
	}
	else if (buttons[2].Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		App->audio->StopMusic();
		return UpdateStatus::STOP;
	}

	return ret;
}

bool ModuleSceneMenu::CleanUp()
{
	LOG("Unloading intro scene");
	bool ret = true;

	return ret;
}
