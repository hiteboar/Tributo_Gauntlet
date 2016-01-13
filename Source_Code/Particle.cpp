#include "Particle.h"
#include "ModuleCollision.h"

	Particle::Particle(fPoint pos, fPoint speed, SDL_Texture* tex, Animation animation, int sound){
		Particle::pos = pos;
		Particle::speed = speed;
		Particle::tex = tex;
		Particle::anim = animation;
		sound_fx = sound;
	}

	Particle::~Particle(){};

	void Particle::AddCollider(Collider* c){
		collider = c;
	}

	void Particle::Move(){
		pos += speed;
		if (collider != nullptr){
			collider->SetPos(pos.x, pos.y);
		}
	}

	float Particle::GetTime(){
		return time.getTime();
	}