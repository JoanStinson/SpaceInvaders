#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
public:
	Asteroid();
	~Asteroid();

	bool Start() override;
	UpdateStatus Update(float delta_time) override;
	bool CleanUp() override;
};

#endif // _ASTEROID_H_
