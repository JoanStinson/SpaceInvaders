#ifndef _MODULETEXTURES_H_
#define _MODULETEXTURES_H_

#include "Module.h"

#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define LAYER_FRONT 0.67F
#define LAYER_MIDDLE 0.62F
#define LAYER_BACK 0.5F
#define LAYER_HUD 0.F

#define DEFAULT_COLOR SDL_Color { 67, 91, 55 }
#define DEFAULT_TEXT_SIZE 24
#define FONT_PATH "Game/candy.ttf"

struct Text
{
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	Text(SDL_Texture* texture)
	{
		Update(texture);
	}

	void Update(SDL_Texture* texture)
	{
		this->texture = texture;
		rect = {};
		SDL_QueryTexture(this->texture, nullptr, nullptr, &rect.w, &rect.h);
	}
};

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init() override;
	bool CleanUp() override;

public:
	SDL_Texture* const LoadImage(const char* path);
	SDL_Texture* const LoadText(const char* text, int size = DEFAULT_TEXT_SIZE, SDL_Color& text_color = DEFAULT_COLOR, bool bold = false, const char* font_path = FONT_PATH);
	void Unload(SDL_Texture* texture);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MODULETEXTURES_H__