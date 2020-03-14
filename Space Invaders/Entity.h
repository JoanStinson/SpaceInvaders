#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;

enum class Tag
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
	Entity(fPoint position, float speed);
	virtual ~Entity();

	virtual bool Start() = 0;
	virtual UpdateStatus Update(float delta_time) = 0;
	virtual bool CleanUp() = 0;

public:
	bool IsEnabled() const;

	void SetPosition(fPoint new_position);
	void SetActive(bool active);
	void SetTexture(SDL_Texture* texture);

	bool HasCollision(const SDL_Rect* entity_rect_a, const SDL_Rect* entity_rect_b);

	Tag GetTag() const;
	SDL_Rect GetBoxCollider() const;

protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	SDL_Rect box_collider;

	fPoint position;
	float speed;

	bool active;

	int life_points;

	Tag tag;
};

#endif // _ENTITY_H_