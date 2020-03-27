#ifndef _MODULETEXTURES_H_
#define _MODULETEXTURES_H_

#include "Module.h"

#include <SDL_render.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>

struct Text
{
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	Text(const SDL_Texture& texture)
	{
		Update(texture);
	}

	void Update(const SDL_Texture& texture)
	{
		this->texture = (SDL_Texture*)&texture;
		rect = {};
		SDL_QueryTexture(this->texture, nullptr, nullptr, &rect.w, &rect.h);
	}
};

class ModuleTexture : public Module
{
public:
	ModuleTexture(bool start_enabled = true);
	~ModuleTexture();

	bool Init() override;
	bool CleanUp() override;

public:
	SDL_Texture* const LoadTexture(const char* path);
	SDL_Texture* const LoadText(const char* text, int size = 24, const SDL_Color& text_color = { 255, 255, 255, 255 }, bool bold = false, const char* font_path = "Assets/Font/space_invaders.ttf");
	void Unload(SDL_Texture* texture);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MODULETEXTURES_H__