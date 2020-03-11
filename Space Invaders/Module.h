#ifndef _MODULE_H_
#define _MODULE_H_

#include "Globals.h"

class Module
{
public:
	Module(bool active = true) : active(active) {}
	virtual ~Module() {}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		return !active ? active = Start() : true;
	}

	bool Disable()
	{
		return active ? active = !CleanUp() : true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual UpdateStatus PreUpdate()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual UpdateStatus Update()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual UpdateStatus PostUpdate()
	{
		return UpdateStatus::CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

private:
	bool active = true;
};

#endif // _MODULE_H_