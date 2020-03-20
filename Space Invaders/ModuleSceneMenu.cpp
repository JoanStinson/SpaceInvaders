#include "ModuleSceneMenu.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGame.h"
#include "Utils.h"

#include <SDL.h>

ModuleSceneMenu::ModuleSceneMenu(bool start_enabled)
	: Module(start_enabled), rect_background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }), rect_logo(SDL_Rect{ 0, 0, 420, 176 })
{
	button_play.rect = { 0, 0, 256, 107 };
	button_play.rect_hover = { 256, 0, 256, 107 };
	button_play.position = fPoint{ (float)(SCREEN_WIDTH / 2) - (button_play.rect.w / 2) - 2, 300 };

	button_credits.rect = { 512, 0, 256, 107 };
	button_credits.rect_hover = { 768, 0, 256, 107 };
	button_credits.position = fPoint{ (float)(SCREEN_WIDTH / 2) - (button_credits.rect.w / 2) - 2, 425 };

	button_exit.rect = { 1024, 0, 256, 107 };
	button_exit.rect_hover = { 1280, 0, 256, 107 };
	button_exit.position = fPoint{ (float)(SCREEN_WIDTH / 2) - (button_exit.rect.w / 2) - 2, 550 };
}

ModuleSceneMenu::~ModuleSceneMenu()
{
}

bool ModuleSceneMenu::Start()
{
	LOG("Loading intro scene");
	bool ret = true;

	texture_background = App->textures->LoadTexture("Sprites/background.jpg");
	texture_logo = App->textures->LoadTexture("Sprites/logo.png");
	texture_buttons = App->textures->LoadTexture("Sprites/buttons.png");

	sfx_hover = App->audio->LoadSfx("Audio/Sfx/hover_button.wav");
	sfx_pressed = App->audio->LoadSfx("Audio/Sfx/click_button.wav");

	App->audio->PlayMusic("Audio/Music/main_theme.mpeg");

	return ret;
}

UpdateStatus ModuleSceneMenu::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	// Draw background and logo
	App->renderer->Draw(texture_background, fPoint(), &rect_background);
	App->renderer->Draw(texture_logo, fPoint{ (float)(SCREEN_WIDTH / 2) - (rect_logo.w / 2) - 2, 60 }, &rect_logo);

	iPoint mouse_pos = App->input->GetMousePosition();
	bool mouse_clicked = App->input->GetMouseButtonDown(1);

	// Play button
	App->renderer->Draw(texture_buttons, button_play.position, &button_play.GetRect(mouse_pos));

	if (button_play.Hovered(mouse_pos) && !button_play.play_hover_audio)
	{
		App->audio->PlaySfx(sfx_hover);
		button_play.play_hover_audio = true;
	}
	else if (!button_play.Hovered(mouse_pos) && button_play.play_hover_audio)
	{
		button_play.play_hover_audio = false;
	}

	if (button_play.Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		App->audio->StopMusic();
		App->fade->FadeToBlack(App->sceneGame.get(), nullptr, 3.f);
	}

	// Credits button
	App->renderer->Draw(texture_buttons, button_credits.position, &button_credits.GetRect(mouse_pos));

	if (button_credits.Hovered(mouse_pos) && !button_credits.play_hover_audio)
	{
		App->audio->PlaySfx(sfx_hover);
		button_credits.play_hover_audio = true;
	}
	else if (!button_credits.Hovered(mouse_pos) && button_credits.play_hover_audio)
	{
		button_credits.play_hover_audio = false;
	}

	if (button_credits.Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		utils::OpenUrl("https://joangm.itch.io");
	}

	// Exit button
	App->renderer->Draw(texture_buttons, button_exit.position, &button_exit.GetRect(mouse_pos));

	if (button_exit.Hovered(mouse_pos) && !button_exit.play_hover_audio)
	{
		App->audio->PlaySfx(sfx_hover);
		button_exit.play_hover_audio = true;
	}
	else if (!button_exit.Hovered(mouse_pos) && button_exit.play_hover_audio)
	{
		button_exit.play_hover_audio = false;
	}

	if (button_exit.Selected(mouse_pos, mouse_clicked))
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
