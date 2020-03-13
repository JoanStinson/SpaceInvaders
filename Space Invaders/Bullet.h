#ifndef _BULLET_H_
#define _BULLET_H_

#include "Creature.h"

class Bullet : public Creature
{
public:
	Bullet();

	bool Start();
	UpdateStatus Update();
	bool CleanUp();
};

#endif // _BULLET_H