#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"

#include <list>

struct SDL_Texture;
struct SDL_Rect;
typedef void (*callback)(void); 

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
	virtual void OnDeath() {};

	void DrawEntity();
	void DrawBoxCollider();
	void ReceiveDamage(int damage, callback on_death = nullptr);

public:
	void SetActive(bool active);
	void SetPosition(fPoint position);
	void SetTexture(SDL_Texture* texture);

	bool IsActive() const;
	bool CompareTag(Type type) const;
	SDL_Rect GetBoxCollider() const;

private:
	void CreateBoxCollider();

public:
	int health;

protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect box_collider;
	SDL_Texture* texture = nullptr;

private:
	bool active = true;
	static std::list<Entity*> entities;
};

#endif // _ENTITY_H_