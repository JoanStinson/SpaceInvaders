#ifndef _BULLET_H_
#define _BULLET_H_

#include "Creature.h"

class Bullet : public Creature
{
public:
	Bullet();
	~Bullet();

	bool Start();
	UpdateStatus Update();
	bool CleanUp();

	void SetPosition(fPoint position);
	void ResetPosition();
};

#endif // _BULLET_H