#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Game.h"
#include "Globals.h"
#include "ModuleCollision.h"
#include "Point.h"
#include "Timer.h"
#include "Animation.h"
#include "ModulePlayer.h"

enum enemy_type;


class Enemy {

protected:
	int health;

#define BLOCK 0
#define ACTIVE 1

	//Animation
	Animation a_right;
	Animation a_left;
	Animation a_up;
	Animation a_down;
	Animation a_up_right;
	Animation a_up_left;
	Animation a_down_left;
	Animation a_down_right;
	Animation* current_anim = nullptr;

	virtual void Continue(){};

	int attack_fx;

public:
	Collider* collider;
	bool dead = false;
	int right = 0, up = 0, left = 0, down = 0;
	fPoint pos;
	float speed = 2;
	enemy_type type;

	Enemy(int h, float x, float y, Module* module, enemy_type t){ 
		health = h;

		pos.x = x;
		pos.y = y;

		SDL_Rect c;
		c.x = x;
		c.y = y;
		c.w = TILE_WIDTH;
		c.h = TILE_HEIGHT;
		collider = game->collider->AddCollider(c, ENEMY_COLLIDER, module);

		current_anim = &a_left;

		type = t;
	};

	virtual ~Enemy(){};

	void Move(){
		int y = abs(game->player->pos.y - pos.y);
		int x = abs(game->player->pos.x - pos.x);
		if (y <= SCREEN_HEIGHT * 2 / 3 && x <= SCREEN_WIDTH / 2){
			Continue();
		}
	};
	
	SDL_Rect* GetCurrentFrame(){

		if (right == ACTIVE && down == BLOCK && up == BLOCK) {
			current_anim = &a_right;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (left == ACTIVE && down == BLOCK && up == BLOCK) {
			current_anim = &a_left;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (up == ACTIVE && right == BLOCK && left == BLOCK) {
			current_anim = &a_up;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (down == ACTIVE && right == BLOCK && left == BLOCK){
			current_anim = &a_down;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (right == ACTIVE && up == ACTIVE){
			current_anim = &a_up_right;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (right == ACTIVE && down == ACTIVE) {
			current_anim = &a_down_right;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (left == ACTIVE && up == ACTIVE) {
			current_anim = &a_up_left;
			if (current_anim->stop) current_anim->stop = false;
		}
		else if (left == ACTIVE && down == ACTIVE) {
			current_anim = &a_down_left;
			if (current_anim->stop) current_anim->stop = false;
		}
		else current_anim->stop = true;

		return &(current_anim->GetCurrentFrame());
	}

	void Hit(){
		health--;
		if (health == 0) dead = true;
	}

	bool invisible = false;


};

#endif // !__ENEMY_H__
