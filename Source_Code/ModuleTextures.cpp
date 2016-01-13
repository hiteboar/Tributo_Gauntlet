#include "Globals.h"
#include "Game.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

using namespace std;

ModuleTextures::ModuleTextures()
{
}

// Destructor
ModuleTextures::~ModuleTextures()
{
	std::list<SDL_Texture*>::iterator it = textures.begin();
	for (it; it != textures.end(); ++it){
		delete *it;
	}

	IMG_Quit();
}

// Called before render is available
bool ModuleTextures::Init()
{
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(game->renderer->renderer, surface);

	textures.push_back(texture);
	SDL_FreeSurface(surface);

	return texture;
}

// Free texture from memory
void ModuleTextures::Unload(SDL_Texture* texture)
{
	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it == texture)
		{
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}