#include "ModuleInput.h"

#include "Application.h"

#include <SDL.h>

ModuleInput::ModuleInput() : Module(), window_events(), mouse_buttons(), mouse_motion({ 0,0 }), mouse_pos({ 0, 0 })
{
	keyboard = new KeyState[MAX_KEYS];

	for (int i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KeyState::IDLE;

	for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i)
		mouse_buttons[i] = KeyState::IDLE;
}

ModuleInput::~ModuleInput()
{
	RELEASE_ARRAY(keyboard);
}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleInput::Start()
{
	return true;
}

UpdateStatus ModuleInput::PreUpdate()
{
	static SDL_Event event;

	mouse_motion = { 0, 0 };

	for (int i = 0; i < (int)EventWindow::COUNT; ++i)
		window_events[i] = false;

	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KeyState::IDLE)
			{
				keyboard[i] = KeyState::DOWN;
			}
			else if (keyboard[i] == KeyState::DOWN)
			{
				keyboard[i] = KeyState::REPEAT;
			}
		}
		else if (keys[i] == 0)
		{
			if (keyboard[i] == KeyState::REPEAT || keyboard[i] == KeyState::DOWN)
			{
				keyboard[i] = KeyState::UP;
			}
			else if (keyboard[i] == KeyState::UP)
			{
				keyboard[i] = KeyState::IDLE;
			}
		}
	}

	for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KeyState::DOWN)
			mouse_buttons[i] = KeyState::REPEAT;

		if (mouse_buttons[i] == KeyState::UP)
			mouse_buttons[i] = KeyState::IDLE;
	}

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			window_events[(int)EventWindow::QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				window_events[(int)EventWindow::HIDE] = true;
				break;

			case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				window_events[(int)EventWindow::SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KeyState::DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KeyState::UP;
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x = event.motion.xrel;
			mouse_motion.y = event.motion.yrel;

			mouse_pos.x = event.motion.x;
			mouse_pos.y = event.motion.y;
			break;
		}
	}

	if (GetWindowEvent(EventWindow::QUIT) || GetKeyDown(SDL_SCANCODE_ESCAPE))
		return UpdateStatus::STOP;

	return UpdateStatus::CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

bool ModuleInput::GetKey(int key) const
{
	return keyboard[key] == KeyState::REPEAT;
}

bool ModuleInput::GetKeyDown(int key) const
{
	return keyboard[key] == KeyState::DOWN;
}

bool ModuleInput::GetKeyUp(int key) const
{
	return keyboard[key] == KeyState::UP;
}

bool ModuleInput::GetMouseButton(int mouse_button) const
{
	return mouse_buttons[mouse_button - 1] == KeyState::REPEAT;
}

bool ModuleInput::GetMouseButtonDown(int mouse_button) const
{
	return mouse_buttons[mouse_button - 1] == KeyState::DOWN;
}

bool ModuleInput::GetMouseButtonUp(int mouse_button) const
{
	return mouse_buttons[mouse_button - 1] == KeyState::UP;
}

bool ModuleInput::GetWindowEvent(EventWindow event) const
{
	return window_events[(int)event];
}

const iPoint& ModuleInput::GetMousePosition() const
{
	return mouse_pos;
}

const iPoint& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}
