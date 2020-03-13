#ifndef _MODULERENDER_H_
#define _MODULERENDER_H_

#include "Module.h"
#include "Point.h"

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
	bool Draw(SDL_Texture* texture, fPoint position, SDL_Rect* section, float speed = 1.f);

	SDL_Renderer& GetRenderer() const;

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // _MODULERENDER_H_