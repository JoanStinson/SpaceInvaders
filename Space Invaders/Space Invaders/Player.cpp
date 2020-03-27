#include "Player.h"

#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

Player::Player()
{
}

Player::Player(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	Entity(rect, rect_collider, texture, animation, texture_death, animation_death, position, life_points, damage, move_speed), init_move_speed(move_speed)
{
	type = Type::PLAYER;

	SDL_Texture* bullet_texture = App->texture->LoadTexture("Assets/Sprites/bullet.png");
	SDL_Texture* bullet_texture_death = App->texture->LoadTexture("Assets/Sprites/blue.png");
	Animation bullet_animation_death(17, 64, 0.8f);

	pooled_bullets.reserve(MAX_BULLETS);

	for (int i = 0; i < MAX_BULLETS; ++i)
		pooled_bullets.push_back(std::move(new Bullet({ 0, 0, 32, 32 }, { 8, 8, 16, 16 }, bullet_texture, bullet_texture_death, bullet_animation_death, fPoint(), 1, 1, 0.5f, this)));

	sfx_shoot = App->audio->LoadSfx("Assets/Audio/Sfx/player_shoot.wav");
	sfx_killed = App->audio->LoadSfx("Assets/Audio/Sfx/player_killed.wav");
}

Player::~Player()
{
	for (int i = 0; i < pooled_bullets.size(); ++i)
		delete pooled_bullets[i];
}

UpdateStatus Player::Update(float delta_time)
{
	if (DrawAnimationDeath(!alive)) 
		return UpdateStatus::CONTINUE;

	// Move right
	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		position.x += move_speed * delta_time;
		move_speed += acceleration * delta_time;

		if (position.x > RIGHT_LIMIT)
			position.x = RIGHT_LIMIT;

		UpdateRectCollider();
	}
	// Move left
	else if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		position.x -= move_speed * delta_time;
		move_speed += acceleration * delta_time;

		if (position.x < LEFT_LIMIT)
			position.x = LEFT_LIMIT;

		UpdateRectCollider();
	}
	else if (App->input->GetKeyUp(SDL_SCANCODE_RIGHT) || App->input->GetKeyUp(SDL_SCANCODE_LEFT))
	{
		move_speed = init_move_speed;
	}

	DrawAnimation();

	// Shoot pooled bullets
	if (App->input->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		App->audio->PlaySfx(sfx_shoot);

		for (int i = 0; i < pooled_bullets.size(); ++i)
		{
			Bullet* bullet = pooled_bullets[i];

			// Instead of new/delete, enable/disable
			if (!bullet->enabled)
			{
				bullet->enabled = true;
				bullet->alive = true;
				bullet->SetPosition(fPoint{ position.x + 14, position.y - 16 });
				break;
			}
		}
	}

	// Update enabled shot bullets
	for (int i = 0; i < pooled_bullets.size(); ++i)
	{
		Bullet* bullet = pooled_bullets[i];

		if (bullet->enabled)
			bullet->Update(delta_time);
	}

	return UpdateStatus::CONTINUE;
}

void Player::OnDeath()
{
	alive = true;
	animation_death.ResetAnim();
}

void Player::PlayKillSound() const
{
	App->audio->PlaySfx(sfx_killed);
}
