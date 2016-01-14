#ifndef __ENEMYSORCERER_H__
#define __ENEMYSORCERER_H__

#include "Globals.h"
#include "Enemy.h"
#include "Point.h"

class EnemySorcerer : public Enemy {

public:
	EnemySorcerer(int health, int x, int y, Module* module);

	void Continue();

private:

	fPoint CalculateObjectivePosition();
	void LookAtPlayer();
	void Attack();

	Timer attack_time;

	Animation attack;

	Timer invisible_timer;

#define INVISIBLE_TIME 500
#define RELOAD_TIME 2000
};

#endif // __ENEMYSORCRER_H_