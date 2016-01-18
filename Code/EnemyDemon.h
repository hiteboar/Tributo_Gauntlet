#ifndef __ENEMYDEMON_H__
#define __ENEMYDEMON_H__

#include "Enemy.h"
#include "Animation.h"
#include "Timer.h"

class EnemyDemon : public Enemy {

public:

	EnemyDemon(int health, int x, int y, Module* module);

	void Continue();

private:

	void ShotParticle();
	fPoint CalculateShotPosition();
	void LookAtPlayer();
	void Shot();

	Timer shot_timer;

	SDL_Rect shot_up;
	SDL_Rect shot_up_right;
	SDL_Rect shot_right;
	SDL_Rect shot_down_right;
	SDL_Rect shot_down;
	SDL_Rect shot_down_left;
	SDL_Rect shot_left;
	SDL_Rect shot_up_left;

#define TILE_SHOT_DISTANCE 4
#define RELOAD_TIME 5000 /*Time in ms*/

};

#endif // __ENEMYDEMON_H__
