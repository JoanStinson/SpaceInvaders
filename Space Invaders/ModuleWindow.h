#ifndef _MODULEWINDOW_H_
#define _MODULEWINDOW_H_

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:
	ModuleWindow(bool start_enabled = true);
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

public:
	SDL_Window& GetWindow() const;

private:
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;
};

#endif // _MODULEWINDOW_H_