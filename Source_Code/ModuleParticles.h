#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Timer.h"
#include "Point.h"
#include <list>

using namespace std;

class Particle;
struct Collider;
enum collider_type;
struct SDL_Texture;

class ModuleParticles : public Module {

public:

	ModuleParticles();
	~ModuleParticles();

	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();


	void OnCollision(Collider* a, Collider* b);
	void AddParticle(fPoint pos, fPoint speed, SDL_Texture* tex, Animation animation ,collider_type c_type, int sound = -1);

private:

	list<Particle* > particles;
	bool player_shoot = false;

	SDL_Texture* graphics;
	Animation impact;
};

#endif // __MODULEPARTICLES_H__