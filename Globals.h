#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "SDL\include\SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

// Deletes a buffer
#define RELEASE( x ) \
	{\
if (x != nullptr)\
	   {\
	   delete x; \
	   x = nullptr; \
	   }\
	}

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{\
if (x != nullptr)\
	   {\
	   delete[] x; \
	   x = nullptr; \
	   }\
	}


#define VSYNC true
#define SCREEN_SIZE 3
#define SCREEN_WIDTH 300//480
#define SCREEN_HEIGHT 200//320
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define TILE_SHEET_SAPCE 2
#define TILE_MAP_WIDTH 32
#define TILE_MAP_HEIGHT 32
#define GAME_NAME "GAUNTLET"

#define SHOT_SPEED 6 

#define TERRAINFILE_PATH "images/terrain.png"
#define ENEMIESFILE_PATH "images/enemies.png"
#define HEROESFILE_PATH "images/heroes.png"
#define MENUFILE_PATH "images/menu.png"
#define LEVEL1_PATH "Levels/Level1.dat"

#define FPS 30

#endif