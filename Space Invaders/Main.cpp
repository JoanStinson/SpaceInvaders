#include "Application.h"
#include "Globals.h"

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

enum class MainState
{
	CREATION,
	START,
	UPDATE,
	FINISH,
	EXIT
};

Application* App = nullptr;

int main(int argc, char** argv)
{
	srand(static_cast<unsigned>(time(NULL)));

	int main_return = EXIT_FAILURE;
	MainState state = MainState::CREATION;

	while (state != MainState::EXIT)
	{
		switch (state)
		{
		case MainState::CREATION:
			LOG("Application Creation --------------");

			App = new Application();
			state = MainState::START;
			break;

		case MainState::START:
			LOG("Application Init --------------");

			if (!App->Init())
			{
				LOG("Application Init exits with error -----");
				state = MainState::EXIT;
			}
			else
			{
				state = MainState::UPDATE;
				LOG("Application Update --------------");
			}
			break;

		case MainState::UPDATE:
		{
			App->delta_time = SDL_GetTicks();

			UpdateStatus update_return = App->Update();

			while (SDL_GetTicks() - App->delta_time < 1000 / FPS);

			if (update_return == UpdateStatus::ERRORS)
			{
				LOG("Application Update exits with error -----");
				state = MainState::EXIT;
			}

			if (update_return == UpdateStatus::STOP)
				state = MainState::FINISH;
		}
		break;

		case MainState::FINISH:
			LOG("Application CleanUp --------------");

			if (!App->CleanUp())
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
			{
				main_return = EXIT_SUCCESS;
			}

			state = MainState::EXIT;
			break;
		}
	}

	RELEASE(App);
	return main_return;
}
