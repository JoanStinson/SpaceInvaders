#ifndef _MODULESCENEMENU_H_
#define _MODULESCENEMENU_H_

#include "Module.h"
#include "Animation.h"

class ModuleSceneMenu : public Module
{
public:
	ModuleSceneMenu(bool start_enabled = true);
	~ModuleSceneMenu();

	bool Start() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

private:

};

#endif // _MODULESCENEMENU_H_