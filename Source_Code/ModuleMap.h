#ifndef __MODULEMAP_H__
#define __MODULEMAP_H__

#include "Module.h"
#include "Game.h"
#include "Globals.h"
#include <vector>

using namespace std;

struct SDL_Texture;

class ModuleMap : public Module
{

public:
	enum levels{
		LEVEL_1,
		LEVEL_2
	};

	enum tile_id {
		WALL,
		GROUND,
		DOOR,
		GHOST_SP,
		DEMON_SP,
		GRUNT_SP,
		SORCERER_SP,
		LOBBER_SP
	};

public:
	ModuleMap();
	~ModuleMap();
	
	bool Start();
	bool Update();
	bool CleanUp();

	void SetLevel(levels lv){ level = lv; }

private:

	levels level = LEVEL_1;

	vector< vector<char> >map;

	 //////// FLAGS ///////			   LDRU
	/*	WALL_UP = 1,				-- 0001
		WALL_RIGHT = 2,				-- 0010
		WALL_RIGHT_UP = 3,			-- 0011
		WALL_DOWN = 4,				-- 0100
		WALL_DOWN_UP = 5,			-- 0101
		WALL_DOWN_RIGHT = 6,		-- 0110
		WALL_DOWN_RIGHT_UP = 7,		-- 0111
		WALL_LEFT = 8,				-- 1000
		WALL_LEFT_UP = 9,			-- 1001
		WALL_LEFT_RIGHT = 10,		-- 1010
		WALL_LEFT_UP_RIGHT = 11,	-- 1011
		WALL_LEFT_DOWN = 12,		-- 1100
		WALL_LEFT_DOWN_UP = 13,		-- 1101 
		WALL_LEFT_DOWN_RIGHT = 14,	-- 1110
		WALL_ALL_DIRECTIONS = 15	-- 1111
	*/

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect wall;

	


	tile_id SelectTile(SDL_Rect& tile, int i, int j, char c);
	int8_t ModuleMap::CheckWallType(int i, int j);
};

#endif //__MODULEMAP_H__