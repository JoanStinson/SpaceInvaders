#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <SDL_rect.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__)

void log(const char file[], int line, const char* format, ...);

enum class UpdateStatus
{
	CONTINUE,
	STOP,
	ERRORS
};

// Deletes a buffer
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Settings
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 720
#define VSYNC true
#define TITLE "Space Invaders"

#endif // _GLOBALS_H_