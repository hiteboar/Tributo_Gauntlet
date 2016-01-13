#include "EnemyDemon.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

EnemyDemon::EnemyDemon(int health, int x, int y, Module* module) : Enemy(health, x, y, module, LOBBER){
	a_up.frames.push_back({ 0, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 0, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up.loop = true;
	a_up.speed = 0.5;

	a_up_right.frames.push_back({ 18, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 18, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.loop = true;
	a_up_right.speed = 0.5;

	a_right.frames.push_back({ 36, 72, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 90, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 108, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 36, 126, TILE_WIDTH, TILE_HEIGHT });
	a_right.loop = true;
	a_right.speed = 0.5;

	a_down_right.frames.push_back({ 54, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 54, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.loop = true;
	a_down_right.speed = 0.5;

	a_down.frames.push_back({ 72, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 72, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down.loop = true;
	a_down.speed = 0.5;

	a_down_left.frames.push_back({ 90, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 90, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.loop = true;
	a_down_left.speed = 0.5;

	a_left.frames.push_back({ 108, 72, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 90, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 108, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 108, 126, TILE_WIDTH, TILE_HEIGHT });
	a_left.loop = true;
	a_left.speed = 0.5;

	a_up_left.frames.push_back({ 126, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 126, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.loop = true;
	a_up_left.speed = 0.5;

	shot_up.x = 198; shot_up.y = 144; shot_up.w = TILE_WIDTH; shot_up.h = TILE_HEIGHT;  
	shot_up_left.x = 198; shot_up_left.y = 162; shot_up_left.w = TILE_WIDTH, shot_up_left.h = TILE_HEIGHT;
	shot_right.x = 198; shot_right.y = 180; shot_right.w = TILE_WIDTH; shot_right.h = TILE_HEIGHT;
	shot_down_right.x = 198; shot_down_right.y = 198; shot_down_right.w = TILE_WIDTH; shot_down_right.h = TILE_HEIGHT;
	shot_down.x = 198; shot_down.y = 216; shot_down.w = TILE_WIDTH; shot_down.h = TILE_HEIGHT;
	shot_down_left.x = 198; shot_down_left.y = 234; shot_down_left.w = TILE_WIDTH; shot_down_left.h = TILE_HEIGHT;
	shot_left.x = 198; shot_left.y = 252; shot_left.w = TILE_WIDTH; shot_left.h = TILE_HEIGHT;
	shot_up_left.x = 198; shot_up_left.y = 270; shot_up_left.w = TILE_WIDTH; shot_up_left.h = TILE_HEIGHT;

	attack_fx = game->audio->LoadFx("Audio/DemonAttack.wav");

}


fPoint EnemyDemon::CalculateShotPosition(){
	list<fPoint> objectives;
	fPoint point;
	int player_x = game->player->pos.x;
	int player_y = game->player->pos.y;

	point.x = player_x +  TILE_WIDTH;
	point.y = player_y;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x += TILE_WIDTH;
		objectives.push_back(point);
	}

	point.x = player_x - TILE_WIDTH;
	point.y = player_y;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x -= TILE_WIDTH;
		objectives.push_back(point);
	}


	point.x = player_x;
	point.y = player_y - TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.y -= TILE_HEIGHT;
		objectives.push_back(point);
	}


	point.x = player_x;
	point.y = player_y + TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.y += TILE_HEIGHT;
		objectives.push_back(point);
	}

	point.x = player_x + TILE_WIDTH;
	point.y = player_y + TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x += TILE_WIDTH;
		point.y += TILE_HEIGHT;
		objectives.push_back(point);
	}

	point.x = player_x - TILE_SHOT_DISTANCE * TILE_WIDTH;
	point.y = player_y + TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x -= TILE_WIDTH;
		point.y += TILE_HEIGHT;
		objectives.push_back(point);
	}

	point.x = player_x - TILE_SHOT_DISTANCE * TILE_WIDTH;
	point.y = player_y - TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x -= TILE_WIDTH;
		point.y -= TILE_HEIGHT;
		objectives.push_back(point);
	}

	point.x = player_x + TILE_SHOT_DISTANCE * TILE_WIDTH;
	point.y = player_y - TILE_HEIGHT;
	objectives.push_back(point);

	for (int i = 1; i < TILE_SHOT_DISTANCE; ++i){
		point.x += TILE_WIDTH;
		point.y -= TILE_HEIGHT;
		objectives.push_back(point);
	}

	fPoint ret;
	float dist = INFINITY;
	list<fPoint>::iterator it;
	for (it = objectives.begin(); it != objectives.end(); ++it){
		float x = abs(it->x - pos.x);
		float y = abs(it->y - pos.y);
		float new_dist = sqrtf(powf(x, 2) + powf(y, 2));
		if (new_dist < dist) {
			ret =(*it);
			dist = new_dist;
		}
	}

	return ret;
}


void EnemyDemon::LookAtPlayer(){

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

void EnemyDemon::Shot(){

	if (shot_timer.getTime() > RELOAD_TIME){
		ShotParticle();
		shot_timer.restart();
	}
}

void EnemyDemon::Continue(){

	fPoint objective = CalculateShotPosition();

	if (objective.x > pos.x - speed && objective.x < pos.x + speed) {
		right = BLOCK;
		left = BLOCK;
		LookAtPlayer(); 
		Shot();
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
		Shot();
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

void EnemyDemon::ShotParticle(){
	fPoint speed;
	fPoint particle_pos;
	Animation anim;
	if (current_anim == &a_up) {
		speed.x = 0;
		speed.y = -SHOT_SPEED;
		particle_pos.x = pos.x;
		particle_pos.y = pos.y - TILE_HEIGHT;
		anim.frames.push_back(shot_up);
	}
	else if (current_anim == &a_right){
		speed.x = SHOT_SPEED;
		speed.y = 0;
		particle_pos.x = pos.x + TILE_WIDTH;
		particle_pos.y = pos.y;
		anim.frames.push_back(shot_right);
	}
	else if (current_anim == &a_up_right){
		speed.x = SHOT_SPEED;
		speed.y = -SHOT_SPEED;
		particle_pos.x = pos.x + TILE_WIDTH;
		particle_pos.y = pos.y - TILE_HEIGHT;
		anim.frames.push_back(shot_up_right);
	}
	else if (current_anim == &a_down){
		speed.x = 0;
		speed.y = SHOT_SPEED;
		particle_pos.x = pos.x;
		particle_pos.y = pos.y + TILE_HEIGHT;
		anim.frames.push_back(shot_down);
	}
	else if (current_anim == &a_down_right){
		speed.x = SHOT_SPEED;
		speed.y = SHOT_SPEED;
		particle_pos.x = pos.x + TILE_WIDTH;
		particle_pos.y = pos.y + TILE_HEIGHT;
		anim.frames.push_back(shot_down_right);
	}
	else if (current_anim == &a_left){
		speed.x = -SHOT_SPEED;
		speed.y = 0;
		particle_pos.x = pos.x - TILE_WIDTH;
		particle_pos.y = pos.y;
		anim.frames.push_back(shot_left);
	}
	else if (current_anim == &a_up_left){
		speed.x = -SHOT_SPEED;
		speed.y = -SHOT_SPEED;
		particle_pos.x = pos.x - TILE_WIDTH;
		particle_pos.y = pos.y - TILE_HEIGHT;
		anim.frames.push_back(shot_up_left);
	}
	else if (current_anim == &a_down_left){
		speed.x = -SHOT_SPEED;
		speed.y = SHOT_SPEED;
		particle_pos.x = pos.x - TILE_WIDTH;
		particle_pos.y = pos.y + TILE_HEIGHT;
		anim.frames.push_back(shot_down_left);
	}

	game->particles->AddParticle(particle_pos, speed, game->enemies->GetGraphics(), anim, DEMON_SHOT_COLLIDER, attack_fx);
}