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

	static void AddEntity(Entity* entity);
	static void RemoveEntity(Entity* entity);

	void DrawEntity();
	void DrawBoxCollider();
	void ReceiveDamage(int damage, callback on_death = nullptr);

	void SetActive(bool active);
	void SetPosition(fPoint position);
	void SetTexture(SDL_Texture* texture);

	bool IsActive() const;
	bool CompareType(Type type) const;
	SDL_Rect GetBoxCollider() const;

private:
	void CreateBoxCollider();

public:
	static std::list<Entity*> entities;
	static bool debug_draw;
	int health;

protected:
	Type type;
	fPoint position;

	SDL_Rect rect;
	SDL_Rect box_collider;
	SDL_Texture* texture = nullptr;

private:
	bool active = true;
};

#endif // _ENTITY_H_