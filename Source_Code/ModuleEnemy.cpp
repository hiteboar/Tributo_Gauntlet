#include "ModuleEnemy.h"
#include "ModuleRender.h"
#include "Game.h"
#include "ModuleTextures.h"
#include "EnemySpawn.h"
#include "EnemyGhost.h"
#include "EnemyLobber.h"
#include "EnemyGrunt.h"
#include "EnemyDemon.h"
#include "EnemySorcerer.h"
#include "ModulePlayer.h"
#include "ModuleMenu.h"

ModuleEnemy::ModuleEnemy(){
	enable = false;
}

ModuleEnemy::~ModuleEnemy(){
	/*list<EnemySpawn* >::iterator sit = spawns.begin(); 
	for (sit; sit != spawns.end(); ++sit){
		delete *sit;
	}

	list<Enemy* >::iterator eit = enemies.begin();
	for (eit; eit != enemies.end(); ++eit){
		 delete *eit;
	}*/
	
}

bool ModuleEnemy::Start(){
	graphics = game->textures->Load(ENEMIESFILE_PATH);
	return true;
}

bool ModuleEnemy::PreUpdate(){


	list<Enemy* >::iterator enemy_it = enemies.begin();

	while (enemy_it != enemies.end()){
		if ((*enemy_it)->dead){
			(*enemy_it)->collider->to_delete = true;
			RELEASE(*enemy_it);
			enemy_it = enemies.erase(enemy_it);
		}
		else ++enemy_it;
	}

	list<EnemySpawn* >::iterator spawn_it = spawns.begin();
	while (spawn_it != spawns.end()){
		if ((*spawn_it)->destroy){
			(*spawn_it)->collider->to_delete = true;
			RELEASE(*spawn_it);
			spawn_it = spawns.erase(spawn_it);
		}
		else ++spawn_it;
	}


	for (enemy_it = enemies.begin(); enemy_it != enemies.end(); enemy_it++){
		(*enemy_it)->Move();
	}
	
	for (spawn_it = spawns.begin(); spawn_it != spawns.end(); spawn_it++){
		(*spawn_it)->PreUpdate();
	}


	return true;
}

bool ModuleEnemy::Update(){

	list<EnemySpawn* >::iterator spawn_it;
	for (spawn_it = spawns.begin(); spawn_it != spawns.end(); ++spawn_it){
		(*spawn_it)->Activate();
	}


	for (spawn_it = spawns.begin(); spawn_it != spawns.end(); ++spawn_it){
		game->renderer->Blit(graphics, (*spawn_it)->x, (*spawn_it)->y, (*spawn_it)->GetCurrentFrame());
	}

	list<Enemy* >::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it){

		(*it)->pos.x += ((*it)->right * (*it)->speed) - ((*it)->left * (*it)->speed);
		(*it)->pos.y += (-(*it)->up * (*it)->speed + (*it)->down * (*it)->speed);

		if (!(*it)->invisible){
			game->renderer->Blit(graphics, (*it)->pos.x, (*it)->pos.y, (*it)->GetCurrentFrame());
		}
		(*it)->collider->SetPos((*it)->pos.x, (*it)->pos.y);

	}


	return true;
}
bool ModuleEnemy::PostUpdate(){

	if (spawns.size() == 0 && enemies.size() == 0) game->menu->Success();

	return true;
}


void ModuleEnemy::IncrementScore(enemy_type type){
	switch (type){
	case GRUNT:
		game->player->score += 10; 
		break;
	case GHOST:
		game->player->score += 10;
		break;
	case DEMON:
		game->player->score += 20;
		break;
	case LOBBER:
		game->player->score += 15;
		break;
	case SORCERER:
		game->player->score += 20;
		break;
	}
}

void ModuleEnemy::OnCollision(Collider* a, Collider* b){
	
	bool exit = false;
	if (a->type == ENEMY_SPAWNPOINT_COLLIDER){
		list<EnemySpawn* >::iterator it = spawns.begin();
		while (it != spawns.end() && !exit){
			if ((*it)->Collide(a)) {
				exit = true;
			}
			else ++it;
		}
	}
	else if (a->type == GRUNT_ATTACK_COLLIDER){
		a->to_delete = true;
	}
	else if (b->type == PLAYER_SHOT_COLLIDER || b->type == DEMON_SHOT_COLLIDER){
		list<Enemy* >::iterator it = enemies.begin();
		while (it != enemies.end() && !exit){
			if ((*it)->collider == a) {
				if (!(*it)->invisible) {
					(*it)->Hit();
					IncrementScore((*it)->type);
				}
				exit = true;
			}
			else ++it;
		}
		if (!exit){
			list<EnemySpawn* >::iterator spawns_it = spawns.begin();
			while (spawns_it != spawns.end() && !exit){
				if ((*spawns_it)->collider == a) {
					(*spawns_it)->Hit();
					exit = true;
				}
				else ++spawns_it;
			}
		}
	}

	else{

		if (b->type == PLAYER_COLLIDER){
			list<Enemy* >::iterator it = enemies.begin();
			while (it != enemies.end() && !exit){
				if ((*it)->collider == a && (*it)->type == GHOST) {
					(*it)->dead = true;
					game->player->Hit(GHOST);
					exit = true;
				}
				else ++it;
			}
		}

		list<Enemy* >::iterator it = enemies.begin();
		while (it != enemies.end() && !exit){
			if ((*it)->collider == a) {
				
				double center_ax = a->rect.x + a->rect.w / 2;
				double center_ay = a->rect.y + a->rect.h / 2;

				double center_bx = b->rect.x + b->rect.w / 2;
				double center_by = b->rect.y + b->rect.h / 2;

				double vector_x = center_bx - center_ax;
				double vector_y = center_by - center_ay;

				double vector_dir = sqrt(pow(vector_x, 2) + pow(vector_y, 2));

				double angle = acos(vector_x / vector_dir);


				if (angle < M_PI / 4 || angle > 7 * M_PI / 4) (*it)->right = BLOCK;
				else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4) (*it)->left = BLOCK;
				else{
					if (center_ay > center_by) (*it)->up = BLOCK;
					else if (center_ay < center_by) (*it)->down = BLOCK;
				}

				exit = true;
			}
			else ++it;
		}
	}
}

void ModuleEnemy::AddEnemy(int x, int y, enemy_type type){

	Enemy* enemy = nullptr;

	switch (type){
	case GHOST:
		enemy = new EnemyGhost (1, x, y, this);
		break;
	case LOBBER:
		enemy = new EnemyLobber (1, x, y, this);
		break;
	case SORCERER:
		enemy = new EnemySorcerer(1, x, y, this);
		break;
	case GRUNT:
		enemy = new EnemyGrunt(1, x, y, this);
		break;
	case DEMON:
		enemy = new EnemyDemon(1, x, y, this);
		break;
	}

	enemies.push_back(enemy);
}

void ModuleEnemy::AddSpawn(int x, int y, enemy_type type){

	EnemySpawn* spawn = new EnemySpawn(x, y, type, this);
	spawns.push_back(spawn);

}

Enemy* ModuleEnemy::GetEnemy(Collider* c){
	list<Enemy* >::iterator it = enemies.begin();
	while (it != enemies.end()){
		if ((*it)->collider == c) return *it;
		++it;
	}
	return nullptr;
}

bool ModuleEnemy::CleanUp(){
	list<EnemySpawn* >::iterator sit = spawns.begin();
	for (sit; sit != spawns.end(); ++sit)
		RELEASE( *sit);

	list<Enemy* >::iterator eit = enemies.begin();
	for (eit; eit != enemies.end(); ++eit)
		RELEASE( *eit);

	spawns.clear();
	enemies.clear();

	return true;
}
