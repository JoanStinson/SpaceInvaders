#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"

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
	virtual ~Entity() {};

	virtual UpdateStatus Update(float delta_time) = 0;

	void DrawEntity();
	//void Entity::ReceiveDamage(int damage);

	void SetPosition(fPoint position);
	void SetTexture(SDL_Texture* texture);

	bool CompareType(Type type) const;
	SDL_Rect GetBoxCollider() const;

private:
	void CreateBoxCollider();
	void DrawBoxCollider();

public:
	int health;
	bool enabled = true;

	static bool debug_draw;

protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect box_collider;
	SDL_Texture* texture = nullptr;
};

#endif // _ENTITY_H_