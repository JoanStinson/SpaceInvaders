#include "Application.h"

#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenu.h"
#include "ModuleSceneGame.h"
 
Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back((input = std::make_unique<ModuleInput>()).get());
	modules.push_back((window = std::make_unique<ModuleWindow>()).get());
	modules.push_back((render = std::make_unique<ModuleRender>()).get());
	modules.push_back((texture = std::make_unique<ModuleTexture>()).get());
	modules.push_back((audio = std::make_unique<ModuleAudio>()).get());
	modules.push_back((scene_menu = std::make_unique<ModuleSceneMenu>(false)).get());
	modules.push_back((scene_game = std::make_unique<ModuleSceneGame>(false)).get());
	modules.push_back((fade = std::make_unique<ModuleFadeToBlack>()).get());
}

Application::~Application()
{
}

bool Application::Init()
{
	bool ret = true;

	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // We init everything, even if not enabled

	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	// Start the first scene 
	fade->FadeToBlack(scene_menu.get(), nullptr, 3.f);

	return ret;
}

UpdateStatus Application::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate();

	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Update();

	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (std::list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->CleanUp();

	return ret;
}
