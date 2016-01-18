#ifndef __MODULEWINDOW_H
#define __MODULEWINDOW_H

#include "Module.h"
#include "Globals.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module {

public:
	ModuleWindow(){};

	bool Init();
	bool CleanUp();

public:

	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;

};

#endif // __MODULEWINDOW_H