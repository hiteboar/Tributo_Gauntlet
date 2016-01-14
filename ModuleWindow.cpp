#include "ModuleWindow.h"
#include "SDL\include\SDL.h"


bool ModuleWindow::Init(){
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) ret = false;
	else {
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_SHOWN;

		window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == nullptr)
		{
			ret = false;
		}
		else
		{
			surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp(){

	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}

