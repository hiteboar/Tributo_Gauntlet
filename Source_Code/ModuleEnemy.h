#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "Globals.h"
#include "Enemy.h"
#include "Point.h"
#include "Animation.h"
#include "EnemySpawn.h"
#include "SDL\include\SDL.h"

#include <list>

using namespace std;


enum enemy_type{
	GHOST,
	DEMON,
	SORCERER,
	LOBBER,
	GRUNT
};


class ModuleEnemy : public Module {

private:

	list< Enemy* > enemies;
	list< EnemySpawn* > spawns;
	SDL_Texture* graphics = nullptr;

public:

	ModuleEnemy();
	~ModuleEnemy(); 

	bool Start();
	bool PreUpdate(); // fixa objectius moviment
	bool Update(); // moviment
	bool PostUpdate(); // actualitza estats

	void IncrementScore(enemy_type type);
	void OnCollision(Collider* a, Collider* b);

	void AddEnemy(int x, int y, enemy_type type);
	void ModuleEnemy::AddSpawn(int x, int y, enemy_type type);

	Enemy* GetEnemy(Collider* c);

	bool CleanUp();

	SDL_Texture* GetGraphics() { return graphics; };
	

};

#endif // __MODULEENEMY_H__
