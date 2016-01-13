#include "EnemySorcerer.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

EnemySorcerer::EnemySorcerer(int health, int x, int y, Module* module) : Enemy(health, x, y, module, GRUNT){

	a_up.frames.push_back({ 0, 144, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 162, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 180, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 198, TILE_WIDTH, TILE_HEIGHT });
	a_up.loop = true;
	a_up.speed = 0.5;

	a_up_right.frames.push_back({ 18, 144, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 162 , TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 180, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 198, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.loop = true;
	a_up_right.speed = 0.5;

	a_right.frames.push_back({ 36, 144, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 162, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 180, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 198, TILE_WIDTH, TILE_HEIGHT });
	a_right.loop = true;
	a_right.speed = 0.5;

	a_down_right.frames.push_back({ 54, 144, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 162, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 180, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 198, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.loop = true;
	a_down_right.speed = 0.5;

	a_down.frames.push_back({ 72, 144, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 162, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 180, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 198, TILE_WIDTH, TILE_HEIGHT });
	a_down.loop = true;
	a_down.speed = 0.5;

	a_down_left.frames.push_back({ 90, 144, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 162, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 180, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 198, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.loop = true;
	a_down_left.speed = 0.5;

	a_left.frames.push_back({ 108, 144, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 162, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 180, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 198, TILE_WIDTH, TILE_HEIGHT });
	a_left.loop = true;
	a_left.speed = 0.5;

	a_up_left.frames.push_back({ 126, 144, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 162, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 180, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 198, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.loop = true;
	a_up_left.speed = 0.5;

	attack.frames.push_back({ 234, 144, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 234, 162, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 234, 180, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 234, 198, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 234, 216, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 234, 234, TILE_WIDTH, TILE_HEIGHT });
	attack.loop = false;
	attack.speed = 2.0;

	attack_fx = game->audio->LoadFx("Audio/SorcererAttack.wav");
}

fPoint EnemySorcerer::CalculateObjectivePosition(){
	fPoint objective[8];

	objective[0].x = game->player->pos.x + TILE_WIDTH;
	objective[0].y = game->player->pos.y;

	objective[1].x = game->player->pos.x - TILE_WIDTH;
	objective[1].y = game->player->pos.y;

	objective[2].x = game->player->pos.x;
	objective[2].y = game->player->pos.y - TILE_HEIGHT;

	objective[3].x = game->player->pos.x;
	objective[3].y = game->player->pos.y + TILE_HEIGHT;

	objective[4].x = game->player->pos.x + TILE_WIDTH;
	objective[4].y = game->player->pos.y + TILE_HEIGHT;

	objective[5].x = game->player->pos.x - TILE_WIDTH;
	objective[5].y = game->player->pos.y + TILE_HEIGHT;

	objective[6].x = game->player->pos.x - TILE_WIDTH;
	objective[6].y = game->player->pos.y - TILE_HEIGHT;

	objective[7].x = game->player->pos.x + TILE_WIDTH;
	objective[7].y = game->player->pos.y - TILE_HEIGHT;

	fPoint ret;
	float dist = INFINITY;

	for (int i = 0; i < 8; ++i){
		float x = objective[i].x - pos.x;
		float y = objective[i].y - pos.x;
		float new_dist = sqrtf(powf(x, 2) + powf(y, 2));
		if (new_dist < dist) {
			ret = objective[i];
			dist = new_dist;
		}
	}

	return ret;
}


void EnemySorcerer::LookAtPlayer(){

	if (game->player->pos.x > pos.x - TILE_WIDTH / 2 && game->player->pos.x < pos.x + TILE_WIDTH / 2 && game->player->pos.y < pos.y) current_anim = &a_up;
	else if (game->player->pos.x > pos.x - TILE_WIDTH / 2 && game->player->pos.x < pos.x + TILE_WIDTH / 2 && game->player->pos.y > pos.y) current_anim = &a_down;
	else if (game->player->pos.x > pos.x && game->player->pos.y > pos.y - TILE_HEIGHT / 2 && game->player->pos.y < pos.y + TILE_HEIGHT / 2) current_anim = &a_right;
	else if (game->player->pos.x < pos.x && game->player->pos.y > pos.y - TILE_HEIGHT / 2 && game->player->pos.y < pos.y + TILE_HEIGHT / 2) current_anim = &a_left;
	else if (game->player->pos.x > pos.x && game->player->pos.y > pos.y) current_anim = &a_down_right;
	else if (game->player->pos.x > pos.x && game->player->pos.y < pos.y) current_anim = &a_up_right;
	else if (game->player->pos.x < pos.x && game->player->pos.y > pos.y) current_anim = &a_down_left;
	else if (game->player->pos.x < pos.x && game->player->pos.y < pos.y) current_anim = &a_up_left;

	current_anim->stop = true;
}

void EnemySorcerer::Attack(){

	if (attack_time.getTime() > RELOAD_TIME){
		fPoint attack_pos;

		if (current_anim == &a_up){
			attack_pos.x = pos.x;
			attack_pos.y = pos.y - TILE_HEIGHT;
		}
		else if (current_anim == &a_down){
			attack_pos.x = pos.x;
			attack_pos.y = pos.y + TILE_HEIGHT;
		}
		else if (current_anim == &a_right){
			attack_pos.x = pos.x + TILE_WIDTH;
			attack_pos.y = pos.y;
		}
		else if (current_anim == &a_left){
			attack_pos.x = pos.x - TILE_WIDTH;
			attack_pos.y = pos.y;
		}
		else if (current_anim == &a_down_right){
			attack_pos.x = pos.x + TILE_WIDTH;
			attack_pos.y = pos.y + TILE_HEIGHT;
		}
		else if (current_anim == &a_up_right){
			attack_pos.x = pos.x + TILE_WIDTH;
			attack_pos.y = pos.y - TILE_HEIGHT;
		}
		else if (current_anim == &a_down_left){
			attack_pos.x = pos.x - TILE_WIDTH;
			attack_pos.y = pos.y + TILE_HEIGHT;
		}
		else if (current_anim == &a_up_left){
			attack_pos.x = pos.x - TILE_WIDTH;
			attack_pos.y = pos.y - TILE_HEIGHT;
		}

		game->particles->AddParticle(attack_pos, { 0, 0 }, game->enemies->GetGraphics(), attack, SORCERER_ATTACK_COLLIDER, attack_fx);
		attack_time.restart();
	}

}

void EnemySorcerer::Continue(){
	invisible = false;
	
	if (invisible_timer.getTime() > INVISIBLE_TIME * 2)invisible_timer.restart();
	else if (invisible_timer.getTime() > INVISIBLE_TIME) invisible = true;


	fPoint objective = CalculateObjectivePosition();

	if (objective.x > pos.x - speed && objective.x < pos.x + speed) {
		right = BLOCK;
		left = BLOCK;
		LookAtPlayer();
		Attack();
	}
	else if (objective.x > pos.x) {
		right = ACTIVE;
		left = BLOCK;
	}
	else{
		right = BLOCK;
		left = ACTIVE;
	}


	if (objective.y > pos.y - speed && objective.y < pos.y + speed) {
		up = BLOCK;
		down = BLOCK;
		LookAtPlayer();
		Attack();
	}
	else if (objective.y > pos.y) {
		down = ACTIVE;
		up = BLOCK;
	}
	else{
		down = BLOCK;
		up = ACTIVE;
	}

}