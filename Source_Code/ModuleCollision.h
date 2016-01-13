#ifndef __MODULECOLLISION_H__
#define __MODULECOLLISION_H__

#include "Module.h"
#include <list>

using namespace std;

class EnemySpawn;

enum collider_type {
	PLAYER_COLLIDER,
	ENEMY_COLLIDER,
	PLAYER_SHOT_COLLIDER,
	WALL_COLLIDER,
	ENEMY_SPAWN_COLLIDER,
	ENEMY_SPAWNPOINT_COLLIDER,
	LOBBER_SHOT_COLLIDER,
	DEMON_SHOT_COLLIDER,
	GRUNT_ATTACK_COLLIDER,
	SORCERER_ATTACK_COLLIDER,

	COLLIDER_MAX,
	NO_COLLIDER
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	collider_type type;
	Module* callback;

	Collider(SDL_Rect rectangle, collider_type type,  Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module {

public:

	ModuleCollision();
	~ModuleCollision();

	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, collider_type type, Module* callback = NULL);

private:
	
	list< Collider* > colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;


};

#endif //__MODULECOLLISION_H__