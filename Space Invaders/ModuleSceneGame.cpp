#include "ModuleSceneGame.h"

#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Animation.h"
#include "Utils.h"
#include "ModuleSceneMenu.h"

ModuleSceneGame::ModuleSceneGame(bool start_enabled) :
	Module(start_enabled), rect_background(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT })
{
	buttons[0].rect = { 0, 0, 256, 107 };
	buttons[0].rect_hover = { 256, 0, 256, 107 };
	buttons[0].position = fPoint{ (float)(SCREEN_WIDTH / 2) - (buttons[0].rect.w / 2) - 2, 375 };

	buttons[1].rect = { 1024, 0, 256, 107 };
	buttons[1].rect_hover = { 1280, 0, 256, 107 };
	buttons[1].position = fPoint{ (float)(SCREEN_WIDTH / 2) - (buttons[1].rect.w / 2) - 2, 500 };
}

ModuleSceneGame::~ModuleSceneGame()
{
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete (*it);

	delete enemy_grid;

	delete lives_title;
	delete score_title;
	delete hiscore_title;

	delete lives_value;
	delete score_value;
	delete hiscore_value;

	delete game_over_title;
}

bool ModuleSceneGame::Start()
{
	LOG("Loading game scene");

	bool ret = true;

	// Load background
	texture_background = App->texture->LoadTexture("Sprites/background.jpg");

	// Generic
	SDL_Texture* entity_texture_death = App->texture->LoadTexture("Sprites/galaxy.png");
	Animation entity_animation_death(17, 64, 0.8f);

	// Load asteroids
	SDL_Texture* asteroid_texture = App->texture->LoadTexture("Sprites/asteroid.png");

	float asteroid_position_y = SCREEN_HEIGHT - (64 * 3) + 20;
	float asteroid_position_x = 15;
	float asteroid_offset_x = 64;

	fPoint asteroid_positions[]
	{
		fPoint{asteroid_position_x, asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 2), asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 4), asteroid_position_y},
		fPoint{asteroid_position_x + (asteroid_offset_x * 6), asteroid_position_y}
	};

	for (int i = 0; i < sizeof(asteroid_positions) / sizeof(asteroid_positions[0]); ++i)
		AddEntity(new Asteroid({ 0, 0, 64, 64 }, { 12, 12, 38, 38 }, asteroid_texture, entity_texture_death, entity_animation_death, asteroid_positions[i], 4));

	// Load enemies
	SDL_Texture* enemy_texture = App->texture->LoadTexture("Sprites/spaceship_enemy.png");
	Animation enemy_animation(8, 64, 0.4f);
	enemy_grid = new EnemyGrid(ROWS, COLS);

	for (int i = 0; i < ROWS; ++i)
	{
		std::vector<Enemy*> enemy_row;

		for (int j = 0; j < COLS; ++j)
		{
			fPoint enemy_position =
			{
				(float)(64 * j) + 25,
				(float)(64 * i) + (48 * 2)
			};

			Enemy* enemy = new Enemy({ 0, 0, 64, 64 }, { 20, 20, 22, 22 }, enemy_texture, enemy_animation, entity_texture_death, entity_animation_death, enemy_position, 1, 1, 10.f);
			enemy_row.push_back(enemy);
			AddEntity(enemy);
		}

		enemy_grid->grid.push_back(enemy_row);
	}

	enemy_grid->CreateGridRects();

	// Load player
	SDL_Texture* player_texture = App->texture->LoadTexture("Sprites/spaceship.png");
	Animation player_animation(8, 64);

	fPoint player_position
	{
		(SCREEN_WIDTH / 2) - 32,
		SCREEN_HEIGHT - 96
	};

	player = new Player({ 0, 0, 64, 64 }, { 12, 26, 40, 16 }, player_texture, player_animation, entity_texture_death, entity_animation_death, player_position, 3, 1, 0.3f);
	AddEntity(player);

	// Load static text
	lives_title = new Text(App->texture->LoadText("LIVES"));
	score_title = new Text(App->texture->LoadText("SCORE"));
	hiscore_title = new Text(App->texture->LoadText("HI-SCORE"));

	// Load dynamic text
	lives_value = new Text(App->texture->LoadText(utils::PadZerosLeft(player->life_points).c_str()));
	score_value = new Text(App->texture->LoadText(utils::PadZerosLeft(score).c_str()));
	hiscore_value = new Text(App->texture->LoadText(utils::PadZerosLeft(hiscore).c_str()));

	// Load game over 
	texture_buttons = App->texture->LoadTexture("Sprites/buttons.png");
	sfx_hover = App->audio->LoadSfx("Audio/Sfx/hover_button.wav");
	sfx_pressed = App->audio->LoadSfx("Audio/Sfx/click_button.wav");
	sfx_game_over = App->audio->LoadSfx("Audio/Sfx/game_over.wav");
	game_over_title = new Text(App->texture->LoadText("GAME OVER", 60, {255, 0, 0, 255}));

	return ret;
}

UpdateStatus ModuleSceneGame::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	// Draw background
	App->render->Draw(texture_background, fPoint(), &rect_background);

	// Draw static text
	App->render->Draw(lives_title->texture, fPoint{ 30, 15 }, &lives_title->rect);
	App->render->Draw(score_title->texture, fPoint{ 170, 15 }, &score_title->rect);
	App->render->Draw(hiscore_title->texture, fPoint{ 310, 15 }, &hiscore_title->rect);

	// Draw dynamic text
	lives_value->Update(App->texture->LoadText(utils::PadZerosLeft(player->life_points).c_str()));
	score_value->Update(App->texture->LoadText(utils::PadZerosLeft(score).c_str()));
	hiscore_value->Update(App->texture->LoadText(utils::PadZerosLeft(hiscore).c_str()));

	App->render->Draw(lives_value->texture, fPoint{ 34, 55 }, &lives_value->rect);
	App->render->Draw(score_value->texture, fPoint{ 181, 55 }, &score_value->rect);
	App->render->Draw(hiscore_value->texture, fPoint{ 340, 55 }, &hiscore_value->rect);

	// While player is not dead play the game
	// When player dies show game over panel
	ret = game_over ? ShowGameOver() : RunGame();

	return ret;
}

UpdateStatus ModuleSceneGame::PostUpdate()
{
	App->texture->Unload(lives_value->texture);
	App->texture->Unload(score_value->texture);
	App->texture->Unload(hiscore_value->texture);
	return UpdateStatus::CONTINUE;
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

void ModuleSceneGame::PlayGameOverSound() const
{
	App->audio->PlaySfx(sfx_game_over);
}

UpdateStatus ModuleSceneGame::RunGame()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	clock.Tick();

	// Update enemy grid
	enemy_grid->Update((float)clock.delta_time);

	// Update entities
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->enabled)
			ret = (*it)->Update((float)clock.delta_time);

	// Toggle box colliders
	//if (App->input->GetKeyDown(SDL_SCANCODE_D))
	//	Entity::debug_draw = !Entity::debug_draw;

	return ret;
}

UpdateStatus ModuleSceneGame::ShowGameOver()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	iPoint mouse_pos = App->input->GetMousePosition();
	bool mouse_clicked = App->input->GetMouseButtonDown(1);

	// Draw text
	App->render->Draw(game_over_title->texture, fPoint{ 55, 200 }, &game_over_title->rect);

	// Draw buttons and handle hovering
	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i)
	{
		App->render->Draw(texture_buttons, buttons[i].position, &buttons[i].GetRect(mouse_pos));

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
		player->life_points = 3;
		score = 0;
		game_over = false;

		for (auto& entity : entities)
		{
			entity->ResetPosition();
			entity->life_points = entity->init_life_points;
			entity->enabled = true;
			entity->alive = true;
		}
	}
	else if (buttons[1].Selected(mouse_pos, mouse_clicked))
	{
		App->audio->PlaySfx(sfx_pressed);
		return UpdateStatus::STOP;
	}

	return ret;
}
