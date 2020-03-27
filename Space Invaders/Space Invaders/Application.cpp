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
	// Order matters: init/start/pre/update/post in this order
	modules.push_back(std::move((input = std::make_unique<ModuleInput>()).get()));
	modules.push_back(std::move((window = std::make_unique<ModuleWindow>()).get()));
	modules.push_back(std::move((render = std::make_unique<ModuleRender>()).get()));
	modules.push_back(std::move((texture = std::make_unique<ModuleTexture>()).get()));
	modules.push_back(std::move((audio = std::make_unique<ModuleAudio>()).get()));
	modules.push_back(std::move((scene_menu = std::make_unique<ModuleSceneMenu>(false)).get()));
	modules.push_back(std::move((scene_game = std::make_unique<ModuleSceneGame>(false)).get()));
	modules.push_back(std::move((fade = std::make_unique<ModuleFadeToBlack>()).get()));
}

Application::~Application()
{
}

bool Application::Init()
{
	bool ret = true;

	for (auto it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); 

	for (auto it = modules.begin(); it != modules.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	// Start the first scene 
	fade->FadeToBlack(scene_menu.get(), nullptr, 3.f);

	return ret;
}

UpdateStatus Application::Update()
{
	UpdateStatus ret = UpdateStatus::CONTINUE;

	for (auto it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate();

	for (auto it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Update();

	for (auto it = modules.begin(); it != modules.end() && ret == UpdateStatus::CONTINUE; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (auto it = modules.rbegin(); it != modules.rend() && ret; ++it)
			ret = (*it)->CleanUp();

	return ret;
}
