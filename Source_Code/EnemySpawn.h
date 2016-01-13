#ifndef __ENEMYSPAWN_H__
#define __ENEMYSPAWN_H__

#include "Timer.h"
#include "ModuleCollision.h"

enum enemy_type;

class EnemySpawn{
public: 

	int x, y;
	bool destroy = false;
	Collider* collider;

public:

	EnemySpawn(int x, int y, enemy_type enemy, Module* module);
	~EnemySpawn();

	void PreUpdate();
	void Activate();

	bool Collide(Collider* a);
	SDL_Rect* GetCurrentFrame();
	void Hit();

private:
	int health = 3;
	Timer time;
	list<pair <Collider*, bool> > spawn_points;

	enemy_type type;

	SDL_Rect texture1;
	SDL_Rect texture2;
	SDL_Rect texture3;

#define SPAWN_TIME 4000

};

#endif // __ENEMYSPAWN_H__
