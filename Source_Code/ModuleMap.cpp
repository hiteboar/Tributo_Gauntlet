#include "ModuleMap.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "Game.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleEnemy.h"
#include "SDL\include\SDL.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ModuleMap::ModuleMap(){
	// ground
	ground.x = 54;
	ground.y = 0;
	ground.w = 16;
	ground.h = 16;

	// wall
	wall.x = 0;
	wall.y = 18;
	wall.w = 16;
	wall.h = 16;

}

ModuleMap::~ModuleMap()
{}

bool ModuleMap::Start()
{

	graphics = game->textures->Load(TERRAINFILE_PATH);

	// load level in memory
	ifstream dataLevel;
	string line;
	dataLevel.open(LEVEL1_PATH);
	while (getline(dataLevel, line)){

		vector<char> map_line;
		for (int i = 0; i < line.length(); ++i){
			if (line[i] == 'p') {
				game->player->pos.x = map_line.size() * TILE_WIDTH;
				game->player->pos.y = map.size() * TILE_HEIGHT;
				map_line.push_back(' ');
			}
			else if (line[i] == 'g'){
				game->enemies->AddSpawn(map_line.size() * TILE_WIDTH, map.size() * TILE_HEIGHT, GHOST);
				map_line.push_back(' ');
			}
			else if (line[i] == 's'){
				game->enemies->AddSpawn(map_line.size() * TILE_WIDTH, map.size() * TILE_HEIGHT, SORCERER);
				map_line.push_back(' ');
			}
			else if (line[i] == 'l'){
				game->enemies->AddSpawn(map_line.size() * TILE_WIDTH, map.size() * TILE_HEIGHT, LOBBER);
				map_line.push_back(' ');
			}
			else if (line[i] == 'd'){
				game->enemies->AddSpawn(map_line.size() * TILE_WIDTH, map.size() * TILE_HEIGHT, DEMON);
				map_line.push_back(' ');
			}
			else if (line[i] == 'r'){
				game->enemies->AddSpawn(map_line.size() * TILE_WIDTH, map.size() * TILE_HEIGHT, GRUNT);
				map_line.push_back(' ');
			}
			else{
				SDL_Rect collider;
				collider.x = map_line.size() * TILE_WIDTH;
				collider.y = map.size() * TILE_HEIGHT;
				collider.h = TILE_HEIGHT;
				collider.w = TILE_WIDTH;

				if (line[i] == '#'){
					game->collider->AddCollider(collider, WALL_COLLIDER);
				}

				map_line.push_back(line[i]);
			}
		}
		map.push_back(map_line);
	}

	return true;
}

// UnLoad assets
bool ModuleMap::CleanUp()
{
	game->textures->Unload(graphics);
	map.clear();
	return true;
}

// Update: draw background
bool ModuleMap::Update()
{

	for (int i = 0; i < map.size(); ++i){
		for (int j = 0; j < map[i].size(); ++j){
			SDL_Rect tile;
			tile_id id = SelectTile(tile, i, j, map[i][j]);
			game->renderer->Blit(graphics, j * TILE_WIDTH, i * TILE_HEIGHT, &tile);
		}
	}

	return true;
}

ModuleMap::tile_id ModuleMap::SelectTile(SDL_Rect& tile, int i ,int j , char c){
	tile_id id;
	switch (c){
	case '#':
	{
		tile = wall;
		_Uint4_t wpos = CheckWallType(i, j);
		tile.x = (TILE_WIDTH + TILE_SHEET_SAPCE) * (wpos - 1);
		id = WALL;
		break;
	}
	case ' ':
		tile = ground;
		id = GROUND;
		break;
	case 'g':
		id = GHOST_SP;
		break;
	case 'd':
		id = DEMON_SP;
		break;
	case 's':
		id = SORCERER_SP;
		break;
	case 'l':
		id = LOBBER_SP;
		break;
	case 'G':
		id = GRUNT_SP;
		break;
	case 'D':
		id = DOOR;
		break;
	}

	return id;
}

int8_t ModuleMap::CheckWallType(int i, int j){
	_Uint4_t flag = 0;
	if (i > 0 && map[i - 1][j] == '#')flag |= 1;
	if (map[i].size() > j + 1 && map[i][j + 1] == '#') flag |= 2;
	if (map.size() > i + 1 && map[i + 1][j] == '#') flag |= 4;
	if (j > 0 && map[i][j - 1] == '#')flag |= 8;

	return flag;
}