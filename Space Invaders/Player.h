#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include "Creature.h"
#include "Bullet.h"

class Player : public Creature
{
public:
	Player();
	Player(fPoint position, float speed);
	~Player();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

private:
	Bullet* bullet = nullptr;
};

#endif // _PLAYER_H_
