#ifndef _MODULEFADETOBLACK_H_
#define _MODULEFADETOBLACK_H_

#include "Module.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(bool start_enabled = true);
	~ModuleFadeToBlack();

	bool Start() override;
	UpdateStatus Update() override;

public:
	void FadeToBlack(Module* module_on, Module* module_off = nullptr, float time = 1.f);
	bool isFading() const;

private:
	bool fading_in = true;

	Uint32 start_time = 0;
	Uint32 total_time = 0;

	Module* module_on = nullptr;
	Module* module_off = nullptr;
};

#endif // _MODULEFADETOBLACK_H_