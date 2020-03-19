#include "ModuleWindow.h"

#include "Application.h"

#include <SDL_image.h>

ModuleWindow::ModuleWindow()
{
}

ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			// Set icon
			SDL_Surface* iconSurface = IMG_Load("Sprites/icon.png");
			SDL_SetWindowIcon(window, iconSurface);
			SDL_FreeSurface(iconSurface);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	// Destroy window
	if (window != nullptr)
	{
		SDL_FreeSurface(screen_surface);
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

SDL_Window& ModuleWindow::GetWindow() const
{
	return *window;
}
