#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Globals.h"
#include "Animation.h"
#include "Point.h"
#include "Game.h"

struct SDL_Texture;
enum enemy_type;

class ModulePlayer : public Module {


public:
	
	ModulePlayer();
	~ModulePlayer();

	bool Init();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool CleanUp();

	void OnCollision(Collider* a, Collider* b);
	void Hit(enemy_type enemy);

	fPoint pos;
	//SDL_Rect* player = nullptr;

	bool shot = false;
	int health = 0;
	int score = 0;

private:
	float speed = 3;
	Collider* collider;
	_Uint4_t mov_flag;

	/*	/// FLAGS ///
		LDRU
		0000 -0- idle
		0001 -1- up
		0010 -2- right
		0011 -3- up_right
		0100 -4- down
		0101 -5- idle
		0110 -6- down_right
		0111 -7- idle
		1000 -8- left
		1001 -9- up_left
		1010 -10- idle
		1011 -11- idle
		1100 -12- down_left
		1101 -13- idle
		1110 -14- idle
		1111 -15- idle 
	*/

#define UP 1
#define RIGHT 2
#define UP_RIGHT 3
#define DOWN 4
#define DOWN_RIGHT 6
#define LEFT 8
#define UP_LEFT 9
#define DOWN_LEFT 12


#define BLOCK_LEFT 7
#define BLOCK_DOWN 11
#define BLOCK_UP 14
#define BLOCK_RIGHT 13



	//Animation
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation up_right;
	Animation up_left;
	Animation down_left;
	Animation down_right;
	Animation* current_anim = nullptr;

	Animation start;

	SDL_Rect shot_up;
	SDL_Rect shot_up_right;
	SDL_Rect shot_right;
	SDL_Rect shot_down_right;
	SDL_Rect shot_down;
	SDL_Rect shot_down_left;
	SDL_Rect shot_left;
	SDL_Rect shot_up_left;


	SDL_Texture* graphics = nullptr;

	int playerAttack_fx;

	void ShotParticle();
};

#endif