#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Module.h"

#include <list>

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleSceneMenu;
class ModuleSceneGame;

class Application {
public:
	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleSceneMenu* sceneIntro = nullptr;
	ModuleSceneGame* sceneGame = nullptr;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // _APPLICATION_H_