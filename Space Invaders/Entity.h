#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Globals.h"
#include "Point.h"

class Entity
{
public:
	Entity();
	Entity(fPoint position, float speed);

	virtual bool Start() = 0;
	virtual UpdateStatus Update() = 0;
	virtual bool CleanUp() = 0;

protected:
	fPoint position;
	float speed;
};

#endif // _ENTITY_H_