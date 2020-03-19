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
	Entity(SDL_Rect rect, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	Entity(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed);
	virtual ~Entity() {};

	virtual UpdateStatus Update(float delta_time) = 0;

	void DrawEntity();
	void DrawAnimation();

	void SetPosition(fPoint position);
	void SetTexture(SDL_Texture* texture);

	bool CompareType(Type type) const;
	SDL_Rect GetBoxCollider() const;
	void DrawBoxCollider();
	void UpdateBoxCollider();
	void SetDefaultBoxCollider();
	void SetBoxCollider(SDL_Rect rect_collider);


public:
	int life_points = 1;
	bool enabled = true;

	static bool debug_draw;

	SDL_Texture* texture = nullptr;
	SDL_Texture* texture_death = nullptr;

	Animation animation;
	Animation animation_death;

	bool dead = false;
	int damage = 1;
	float move_speed;
protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect box_collider;

};

#endif // _ENTITY_H_