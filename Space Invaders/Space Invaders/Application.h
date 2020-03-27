#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Module.h"

#include <list>
#include <memory>

class ModuleRender;
class ModuleWindow;
class ModuleTexture;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleSceneMenu;
class ModuleSceneGame;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

public:
	std::unique_ptr<ModuleRender> render;
	std::unique_ptr<ModuleWindow> window;
	std::unique_ptr<ModuleTexture> texture;
	std::unique_ptr<ModuleInput> input;
	std::unique_ptr<ModuleAudio> audio;
	std::unique_ptr<ModuleFadeToBlack> fade;
	std::unique_ptr<ModuleSceneMenu> scene_menu;
	std::unique_ptr<ModuleSceneGame> scene_game;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // _APPLICATION_H_