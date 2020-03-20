#ifndef _MODULEINPUT_H_
#define _MODULEINPUT_H_

#include "Module.h"
#include "Point.h"

#include <SDL_scancode.h>

#define MAX_KEYS 286
#define MAX_MOUSE_BUTTONS 5

enum class EventWindow
{
	QUIT,
	HIDE,
	SHOW,
	COUNT
};

enum class KeyState
{
	IDLE,
	DOWN,
	REPEAT,
	UP
};

enum class MouseMove
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class ModuleInput : public Module
{
public:
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	UpdateStatus PreUpdate() override;
	bool CleanUp() override;

public:
	bool GetWindowEvent(EventWindow code) const;

	bool GetKey(int key) const;
	bool GetKeyDown(int key) const;
	bool GetKeyUp(int key) const;

	bool GetMouseButton(int mouse_button) const;
	bool GetMouseButtonDown(int mouse_button) const;
	bool GetMouseButtonUp(int mouse_button) const;

	const iPoint& GetMouseMotion() const;
	const iPoint& GetMousePosition() const;

private:
	bool window_events[(int)EventWindow::COUNT];

	KeyState* keyboard = nullptr;
	KeyState mouse_buttons[MAX_MOUSE_BUTTONS];

	iPoint mouse_motion;
	iPoint mouse_pos;
};

#endif // __MODULEINPUT_H__