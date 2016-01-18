#pragma once

#include "Globals.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;
struct SDL_Rect;
class Collider;

class Particle {
private:
	Timer time;

public:
	fPoint pos;
	fPoint speed;
	SDL_Texture* tex;
	Animation anim;
	Collider* collider = nullptr;
	bool destroy = false;
	int sound_fx;

public:
	Particle(fPoint pos, fPoint speed, SDL_Texture* tex, Animation animation, int sound);

	~Particle();

	void AddCollider(Collider* c);

	void Move();

	float GetTime();
};