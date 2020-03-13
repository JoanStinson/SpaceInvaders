#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include "Creature.h"
#include "Bullet.h"

#include <vector>

#define MAX_BULLETS 20

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

	std::vector<Bullet*> pooled_bullets;
};

#endif // _PLAYER_H_
