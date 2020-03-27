#ifndef _BUTTON_H
#define _BUTTON_H

#include "Point.h"

struct SDL_Texture;
struct SDL_Rect;

struct Button
{
	SDL_Rect rect;
	SDL_Rect rect_hover;
	fPoint position;
	bool play_hover_audio = false;

	bool Hovered(iPoint mouse_pos)
	{
		bool inside_width = (mouse_pos.x > position.x) && (mouse_pos.x < (position.x + rect.w));
		bool inside_height = (mouse_pos.y > position.y) && (mouse_pos.y < (position.y + rect.h));

		return inside_width && inside_height;
	}

	bool Selected(iPoint mouse_pos, bool mouse_clicked)
	{
		return (Hovered(mouse_pos) && mouse_clicked) ? true : false;
	}

	SDL_Rect GetRect(iPoint mouse_pos)
	{
		return Hovered(mouse_pos) ? rect_hover : rect;
	}
};

#endif // _BUTTON_H