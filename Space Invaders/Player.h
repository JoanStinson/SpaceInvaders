#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bullet.h"

#include <vector>

struct SDL_Texture;
struct SDL_Rect;
struct SDL_Button_t;

class Player : public Entity
{
public:
	Player();
	Player(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	~Player();

	UpdateStatus Update(float delta_time) override;
	int score = 0;
	int high_score = 0;
private:
	std::vector<Bullet*> pooled_bullets;

	SDL_Texture* bulletTexture = nullptr;

	const int MAX_BULLETS = 50;
};

#endif // _PLAYER_H_
