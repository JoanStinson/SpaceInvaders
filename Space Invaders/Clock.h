#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <SDL_timer.h>

struct Clock
{
	Uint64 current_time = SDL_GetPerformanceCounter();
	Uint64 last_time = 0;
	double delta_time = 0;

	void Tick()
	{
		last_time = current_time;
		current_time = SDL_GetPerformanceCounter();
		delta_time = ((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());
	}
};

#endif // _CLOCK_H_