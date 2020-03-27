#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SDL_rect.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__)

static const char* TITLE = "Space Invaders";
static const int SCREEN_WIDTH = 480;
static const int SCREEN_HEIGHT = 720;
static const bool VSYNC = true;

void log(const char file[], int line, const char* format, ...);

enum class UpdateStatus
{
	CONTINUE,
	STOP,
	ERRORS
};

#endif // _GLOBALS_H_