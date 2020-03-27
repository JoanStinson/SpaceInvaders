#include "ModuleTexture.h"

#include "Application.h"
#include "ModuleRender.h"

ModuleTexture::ModuleTexture(bool start_enabled) : Module(start_enabled)
{
}

ModuleTexture::~ModuleTexture()
{
	IMG_Quit();
	TTF_Quit();
}

bool ModuleTexture::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTexture::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (auto it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
	return true;
}

SDL_Texture* const ModuleTexture::LoadTexture(const char* path)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(&App->render->GetRenderer(), surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures.push_back(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

SDL_Texture* const ModuleTexture::LoadText(const char* text, int size, const SDL_Color& text_color, bool bold, const char* font_path)
{
	SDL_Texture* texture = nullptr;
	TTF_Font* font = TTF_OpenFont(font_path, size);

	if (font == nullptr)
	{
		LOG("Could not load font with path: %s. TTF_Load: %s", font_path, TTF_GetError());
	}
	else
	{
		if (bold)
			TTF_SetFontStyle(font, TTF_STYLE_BOLD);

		SDL_Surface* surface = TTF_RenderText_Blended(font, text, text_color);

		if (surface == nullptr)
		{
			LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(&App->render->GetRenderer(), surface);

			if (texture == nullptr)
			{
				LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				textures.push_back(texture);
			}

			SDL_FreeSurface(surface);
		}

		TTF_CloseFont(font);
	}

	return texture;
}

void ModuleTexture::Unload(SDL_Texture* texture)
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it == texture)
		{
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}
