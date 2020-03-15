#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <SDL_timer.h>

struct Clock
{
	Uint64 current_time = SDL_GetPerformanceCounter();
	Uint64 last_time = 0;
	double delta_time = 0;

	Uint32 current_invoke_time = 0;
	Uint32 last_invoke_time = 0;

	void Tick()
	{
		last_time = current_time;
		current_time = SDL_GetPerformanceCounter();
		delta_time = ((current_time - last_time) * 1000 / (double)SDL_GetPerformanceFrequency());

		current_invoke_time = SDL_GetTicks();
	}

	template <typename CallableObject>
	void Invoke(float delay_seconds, CallableObject callback) 
	{
		if (current_invoke_time > last_invoke_time + (delay_seconds * 100) * delta_time)
		{
			callback();
			last_invoke_time = current_invoke_time;
			LOG("Invoke");
		}
	}
};

#endif // _CLOCK_H_