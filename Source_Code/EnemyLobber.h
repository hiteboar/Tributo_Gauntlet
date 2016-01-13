#ifndef __ENEMYLOBBER_H__
#define __ENEMYLOBBER_H__

#include "Enemy.h"
#include "Animation.h"
#include "Timer.h"

class EnemyLobber : public Enemy {

public:

	EnemyLobber(int health, int x, int y, Module* module);

	void Continue();

private:

	Animation rock_particle;

	void ShotParticle();
	fPoint CalculateObjectivePosition();
	void LookAtPlayer();
	void Shot();

	Timer shot_timer;

#define MIN_DISTANCE 4*TILE_WIDTH
#define RELOAD_TIME 3000 /*Time in ms*/

};

#endif // __ENEMYLOBBER_H__
