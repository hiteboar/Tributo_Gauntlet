#ifndef __ENEMYGRUNT_H__
#define __ENEMYGRUNT_H__

#include "Globals.h"
#include "Enemy.h"
#include "Point.h"

class EnemyGrunt : public Enemy {

public:
	EnemyGrunt(int health, int x, int y, Module* module);

	void Continue();

private:

	fPoint CalculateObjectivePosition();
	void LookAtPlayer(); 
	void Attack();

	Timer attack_time;

	Animation attack;

#define RELOAD_TIME 1000
};

#endif // __ENEMYGRUNT_H_