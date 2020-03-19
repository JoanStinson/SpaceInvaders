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
	Entity() {}
	Entity(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health);
	Entity(SDL_Texture* texture, Animation animation, SDL_Rect rect, fPoint position, int health);
	virtual ~Entity() {};

	virtual UpdateStatus Update(float delta_time) = 0;

	void DrawEntity();
	void DrawAnimation();
	//void Entity::ReceiveDamage(int damage);

	void SetPosition(fPoint position);
	void SetTexture(SDL_Texture* texture);

	bool CompareType(Type type) const;
	SDL_Rect GetBoxCollider() const;
	void DrawBoxCollider();
private:
	void CreateBoxCollider();


public:
	int health;
	bool enabled = true;

	static bool debug_draw;

	SDL_Texture* die_texture;
	Animation die_animation;
	bool isDead = false;
protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect box_collider;
	SDL_Texture* texture = nullptr;
	Animation animation;
};

#endif // _ENTITY_H_