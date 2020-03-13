#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;

class Entity
{
public:
	Entity();
	Entity(fPoint position, float speed);
	virtual ~Entity();

	virtual bool Start() = 0;
	virtual UpdateStatus Update() = 0;
	virtual bool CleanUp() = 0;

public:
	bool IsEnabled() const;

	void SetPosition(fPoint new_position);
	void SetActive(bool active);
	void SetTexture(SDL_Texture* texture);

protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	fPoint position;
	float speed;

	bool active;
};

#endif // _ENTITY_H_