#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"
#include "Animation.h"

#include <list>

struct SDL_Texture;
struct SDL_Rect;

enum class Type
{
	PLAYER,
	BULLET,
	ASTEROID,
	ENEMY
};

class Entity
{
public:
	Entity();
	Entity(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	Entity(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	virtual ~Entity() {};

	virtual UpdateStatus Update(float delta_time) = 0;
	virtual void OnDeath() = 0;

	void Draw();
	void DrawAnimation();
	bool DrawAnimationDeath(bool condition_death);
	bool DrawAnimationDeath(bool condition_death, fPoint position_death);

	bool CompareType(Type type) const;
	SDL_Rect GetRectCollider() const;
	fPoint GetPosition() const;

	void SetPosition(fPoint position);
	void UpdateRectCollider();

private:
	void DrawRectCollider();

public:
	bool enabled = true;
	bool alive = true;

	int life_points;
	static bool debug_draw;

protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect rect_collider;
	SDL_Rect init_rect_collider;

	Animation animation;
	Animation animation_death;

	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_death = nullptr;

	int damage;
	float move_speed;
};

#endif // _ENTITY_H_