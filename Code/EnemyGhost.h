#ifndef __ENEMYGHOST_H__
#define __ENEMYGHOST_H__

#include "Enemy.h"

class EnemyGhost : public Enemy {

public:

	EnemyGhost(int health, int x, int y, Module* module);

	void Continue();

};

#endif // __ENEMYGHOST_H__
