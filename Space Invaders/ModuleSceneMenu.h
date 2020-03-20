#ifndef _MODULESCENEMENU_H_
#define _MODULESCENEMENU_H_

#include "Module.h"
#include "SDL_Button.h"

enum class MouseMove;
struct SDL_Texture;
struct SDL_Rect;

class ModuleSceneMenu : public Module
{
public:
	ModuleSceneMenu(bool start_enabled = true);
	~ModuleSceneMenu();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* texture_background = nullptr;
	SDL_Rect rect_background;

	SDL_Texture* texture_logo = nullptr;
	SDL_Rect rect_logo;

	SDL_Texture* texture_buttons = nullptr;
};

#endif // _MODULESCENEMENU_H_