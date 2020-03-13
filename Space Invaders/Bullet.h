#ifndef _BULLET_H_
#define _BULLET_H_

#include "Creature.h"

class Bullet : public Creature
{
public:
	Bullet();
	~Bullet();

	bool Start() override;
	UpdateStatus Update(float delta_time) override;
	bool CleanUp() override;
};

#endif // _BULLET_H