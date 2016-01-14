#include "EnemySpawn.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModulePlayer.h"



EnemySpawn::EnemySpawn(int x, int y, enemy_type enemy, Module* module){
	type = enemy;

	EnemySpawn::x = x;
	EnemySpawn::y = y; 

	if (type == GHOST){
		texture1.x = 144; texture1.y = 144; texture1.w = TILE_WIDTH; texture1.h = TILE_HEIGHT;
		texture2.x = 144; texture2.y = 162; texture2.w = TILE_WIDTH; texture2.h = TILE_HEIGHT;
		texture3.x = 144; texture3.y = 180; texture3.w = TILE_WIDTH; texture3.h = TILE_HEIGHT;
	}
	else{
		texture1.x = 162; texture1.y = 144; texture1.w = TILE_WIDTH; texture1.h = TILE_HEIGHT;
		texture2.x = 162; texture2.y = 162; texture2.w = TILE_WIDTH; texture2.h = TILE_HEIGHT;
		texture3.x = 162; texture3.y = 180; texture3.w = TILE_WIDTH; texture3.h = TILE_HEIGHT;
	}

	SDL_Rect c_quad;
	c_quad.x = x; c_quad.y = y; c_quad.w = TILE_WIDTH; c_quad.h = TILE_HEIGHT;
	collider = game->collider->AddCollider(c_quad, ENEMY_SPAWN_COLLIDER, module);

	c_quad.x = x - TILE_WIDTH;
	Collider* c_temp = game->collider->AddCollider(c_quad, ENEMY_SPAWNPOINT_COLLIDER, module);
	spawn_points.push_back(pair<Collider*, bool>(c_temp, false));

	c_quad.x = x + TILE_WIDTH;
	c_temp = game->collider->AddCollider(c_quad, ENEMY_SPAWNPOINT_COLLIDER, module);
	spawn_points.push_back(pair<Collider*, bool>(c_temp, false));
	
	c_quad.x = x; c_quad.y = y - TILE_HEIGHT;
	c_temp = game->collider->AddCollider(c_quad, ENEMY_SPAWNPOINT_COLLIDER, module);
	spawn_points.push_back(pair<Collider*, bool>(c_temp, false));

	c_quad.y = y + TILE_HEIGHT;
	c_temp = game->collider->AddCollider(c_quad, ENEMY_SPAWNPOINT_COLLIDER, module);
	spawn_points.push_back(pair<Collider*, bool>(c_temp, false));

	
}

EnemySpawn::~EnemySpawn(){
	/*list<pair <Collider*, bool> >::iterator it;

	for (it = spawn_points.begin(); it != spawn_points.end(); ++it){
		it->first->to_delete = true;
	}*/
}

void EnemySpawn::PreUpdate(){
	list<pair< Collider*, bool> >::iterator it = spawn_points.begin();
	while (it != spawn_points.end()){
		it->second = false;
		++it;
	}

}

void EnemySpawn::Activate(){
	float dist_x = abs(game->player->pos.x - x);
	float dist_y = abs(game->player->pos.y - y);
	if (dist_x < SCREEN_WIDTH && dist_y < SCREEN_HEIGHT && time.getTime() > SPAWN_TIME){

		list<pair< Collider*, bool> >::iterator it = spawn_points.begin();
		while (it != spawn_points.end()){
			if (!it->second) {
				game->enemies->AddEnemy(it->first->rect.x, it->first->rect.y, type);
			}
			++it;
		}
		time.restart();
	}

}

bool EnemySpawn::Collide(Collider* a){
	list<pair< Collider*, bool> >::iterator it = spawn_points.begin();
	bool exit = false;
	while (it != spawn_points.end() && !exit){
		if (a == it->first){
			it->second = true;
			exit = true;
		}
		++it;
	}

	return exit;
}

void EnemySpawn::Hit(){
	--health;
	if (health == 0){
		list< pair <Collider*, bool> >::iterator it;
		for (it = spawn_points.begin(); it != spawn_points.end(); ++it){
			(*it).first->to_delete = true;
		}

		destroy = true;
	}
}

SDL_Rect* EnemySpawn::GetCurrentFrame(){
	switch (health){
	case 3:
		return &texture1;
		break;
	case 2:
		return &texture2;
		break;
	case 1:
		return &texture3;
		break;
	}
}
