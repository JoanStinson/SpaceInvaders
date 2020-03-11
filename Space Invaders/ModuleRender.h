#ifndef _MODULERENDER_H_
#define _MODULERENDER_H_

#include "Module.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;

public:
	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0F);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // _MODULERENDER_H_