#include "Globals.h"
#include "Game.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "EnemySpawn.h"

using namespace std;

ModuleCollision::ModuleCollision() : Module()
{
	debug = false;

	// Matrix is game specific, change it to adapt to your own needs
	// ... think of moving this outside ModuleCollision
	matrix[WALL_COLLIDER][WALL_COLLIDER] = false;
	matrix[WALL_COLLIDER][PLAYER_COLLIDER] = false;
	matrix[WALL_COLLIDER][ENEMY_COLLIDER] = false;
	matrix[WALL_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[WALL_COLLIDER][ENEMY_SPAWN_COLLIDER] = false;
	matrix[WALL_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[WALL_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[WALL_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[WALL_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[PLAYER_COLLIDER][WALL_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][PLAYER_COLLIDER] = false;
	matrix[PLAYER_COLLIDER][ENEMY_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[PLAYER_COLLIDER][ENEMY_SPAWN_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[PLAYER_COLLIDER][LOBBER_SHOT_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][DEMON_SHOT_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][GRUNT_ATTACK_COLLIDER] = true;
	matrix[PLAYER_COLLIDER][SORCERER_ATTACK_COLLIDER] = true;

	matrix[ENEMY_COLLIDER][WALL_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][ENEMY_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][PLAYER_SHOT_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][ENEMY_SPAWN_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[ENEMY_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[ENEMY_COLLIDER][DEMON_SHOT_COLLIDER] = true;
	matrix[ENEMY_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[ENEMY_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[PLAYER_SHOT_COLLIDER][WALL_COLLIDER] = true;
	matrix[PLAYER_SHOT_COLLIDER][PLAYER_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][ENEMY_COLLIDER] = true;
	matrix[PLAYER_SHOT_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][ENEMY_SPAWN_COLLIDER] = true;
	matrix[PLAYER_SHOT_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[PLAYER_SHOT_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[ENEMY_SPAWN_COLLIDER][WALL_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][PLAYER_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][ENEMY_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][PLAYER_SHOT_COLLIDER] = true;
	matrix[ENEMY_SPAWN_COLLIDER][ENEMY_SPAWN_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][DEMON_SHOT_COLLIDER] = true;
	matrix[ENEMY_SPAWN_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[ENEMY_SPAWN_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[ENEMY_SPAWNPOINT_COLLIDER][WALL_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][ENEMY_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][PLAYER_SHOT_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][ENEMY_SPAWN_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][DEMON_SHOT_COLLIDER] = true;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[ENEMY_SPAWNPOINT_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[LOBBER_SHOT_COLLIDER][WALL_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[LOBBER_SHOT_COLLIDER][ENEMY_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][ENEMY_SPAWN_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[LOBBER_SHOT_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[DEMON_SHOT_COLLIDER][WALL_COLLIDER] = true;
	matrix[DEMON_SHOT_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[DEMON_SHOT_COLLIDER][ENEMY_COLLIDER] = true;
	matrix[DEMON_SHOT_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[DEMON_SHOT_COLLIDER][ENEMY_SPAWN_COLLIDER] = true;
	matrix[DEMON_SHOT_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[DEMON_SHOT_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[DEMON_SHOT_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[DEMON_SHOT_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[DEMON_SHOT_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[GRUNT_ATTACK_COLLIDER][WALL_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[GRUNT_ATTACK_COLLIDER][ENEMY_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][ENEMY_SPAWN_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[GRUNT_ATTACK_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;

	matrix[SORCERER_ATTACK_COLLIDER][WALL_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][PLAYER_COLLIDER] = true;
	matrix[SORCERER_ATTACK_COLLIDER][ENEMY_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][PLAYER_SHOT_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][ENEMY_SPAWN_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][ENEMY_SPAWNPOINT_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][LOBBER_SHOT_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][DEMON_SHOT_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][GRUNT_ATTACK_COLLIDER] = false;
	matrix[SORCERER_ATTACK_COLLIDER][SORCERER_ATTACK_COLLIDER] = false;
}

ModuleCollision::~ModuleCollision(){
	/*for (list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);*/
}

bool ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			if ((*it)->type == PLAYER_SHOT_COLLIDER) game->player->shot = false;
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return true;
}

// Called before render is available
bool ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		c1 = *it;

		for (list<Collider*>::iterator it2 = it; it2 != colliders.end(); ++it2)
		{
			c2 = *it2;

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;;
}

// Called before render is available
bool ModuleCollision::PostUpdate()
{
	if (game->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
	{
		for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		{
			Collider* col = *it;
			Uint8 alpha = 100;
			switch (col->type)
			{
			case WALL_COLLIDER:
				game->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
			case PLAYER_COLLIDER:
				game->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
			case ENEMY_COLLIDER:
				game->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
			case PLAYER_SHOT_COLLIDER:
				game->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;
			case LOBBER_SHOT_COLLIDER:
			case DEMON_SHOT_COLLIDER:
				game->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
				break;
			case ENEMY_SPAWN_COLLIDER:
				game->renderer->DrawQuad(col->rect, 255, 0, 255, alpha);
				break;
			case ENEMY_SPAWNPOINT_COLLIDER:
				game->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
				break;
			}
		}
	}

	return true;
}

// Called before quitting
bool ModuleCollision::CleanUp(){

	for (list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);
	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, collider_type type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret);
	return ret;
}


bool Collider::CheckCollision(SDL_Rect r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}