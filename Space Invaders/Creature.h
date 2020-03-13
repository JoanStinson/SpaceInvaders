#ifndef _CREATURE_H_
#define _CREATURE_H

#include "Entity.h"

class Creature : public Entity
{
public:
	Creature();
	Creature(fPoint position, float speed);

	virtual bool Start() = 0;
	virtual UpdateStatus Update(float delta_time) = 0;
	virtual bool CleanUp() = 0;
};

#endif // _CREATURE_H_
