#include "EnemyGhost.h"
#include "Game.h"
#include "ModuleEnemy.h"

EnemyGhost::EnemyGhost(int hd, int x, int y, Module* module) : Enemy(hd, x, y, module, GHOST) {

	a_up.frames.push_back({ 0, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up.loop = true;
	a_up.speed = 0.5;

	a_up_right.frames.push_back({ 18, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.loop = true;
	a_up_right.speed = 0.5;

	a_right.frames.push_back({ 36, 0, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 18, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 36, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 54, TILE_WIDTH, TILE_HEIGHT });
	a_right.loop = true;
	a_right.speed = 0.5;

	a_down_right.frames.push_back({ 54, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.loop = true;
	a_down_right.speed = 0.5;

	a_down.frames.push_back({ 72, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down.loop = true;
	a_down.speed = 0.5;

	a_down_left.frames.push_back({ 90, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.loop = true;
	a_down_left.speed = 0.5;

	a_left.frames.push_back({ 108, 0, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 18, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 36, TILE_WIDTH, TILE_HEIGHT });	
	a_left.frames.push_back({ 108, 54, TILE_WIDTH, TILE_HEIGHT });
	a_left.loop = true;
	a_left.speed = 0.5;

	a_up_left.frames.push_back({ 126, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.loop = true;
	a_up_left.speed = 0.5;
}

void EnemyGhost::Continue(){
	if (game->player->pos.x > pos.x - speed  && game->player->pos.x < pos.x + speed) {
		right = BLOCK;
		left = BLOCK;
	}
	else if (game->player->pos.x > pos.x) {
		right = ACTIVE;
		left = BLOCK;
	}
	else{
		right = BLOCK;
		left = ACTIVE;
	}


	if (game->player->pos.y > pos.y - speed && game->player->pos.y < pos.y + speed) {
		up = BLOCK;
		down = BLOCK;
	}
	else if (game->player->pos.y > pos.y) {
		down = ACTIVE;
		up = BLOCK;
	}
	else{
		down = BLOCK;
		up = ACTIVE;
	}

}