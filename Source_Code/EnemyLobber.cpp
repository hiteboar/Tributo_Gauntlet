#include "EnemyLobber.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

EnemyLobber::EnemyLobber(int health, int x, int y, Module* module) : Enemy (health, x, y, module, LOBBER){
	a_up.frames.push_back({ 144, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up.loop = true;
	a_up.speed = 0.5;

	a_up_right.frames.push_back({ 162, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.loop = true;
	a_up_right.speed = 0.5;

	a_right.frames.push_back({ 180, 72, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 90, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 108, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 126, TILE_WIDTH, TILE_HEIGHT });
	a_right.loop = true;
	a_right.speed = 0.5;

	a_down_right.frames.push_back({ 198, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.loop = true;
	a_down_right.speed = 0.5;

	a_down.frames.push_back({ 216, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down.loop = true;
	a_down.speed = 0.5;

	a_down_left.frames.push_back({ 234, 72, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 90, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 108, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 126, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.loop = true;
	a_down_left.speed = 0.5;

	a_left.frames.push_back({ 252, 72, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 90, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 108, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 126, TILE_WIDTH, TILE_HEIGHT });
	a_left.loop = true;
	a_left.speed = 0.5;

	a_up_left.frames.push_back({ 270, 72, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 90, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 108, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 126, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.loop = true;
	a_up_left.speed = 0.5;

	rock_particle.frames.push_back({ 180, 216, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 198, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 180, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 162, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 144, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 162, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 180, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 198, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.frames.push_back({ 180, 216, TILE_WIDTH, TILE_HEIGHT });
	rock_particle.loop = false;
	rock_particle.speed = 0.4;

	attack_fx = game->audio->LoadFx("Audio/LobberAttack.wav");

}


fPoint EnemyLobber::CalculateObjectivePosition(){
	fPoint objective[8];

	objective[0].x = game->player->pos.x + MIN_DISTANCE;
	objective[0].y = game->player->pos.y;

	objective[1].x = game->player->pos.x - MIN_DISTANCE;
	objective[1].y = game->player->pos.y;

	objective[2].x = game->player->pos.x;
	objective[2].y = game->player->pos.y - MIN_DISTANCE;

	objective[3].x = game->player->pos.x;
	objective[3].y = game->player->pos.y + MIN_DISTANCE;

	objective[4].x = game->player->pos.x + MIN_DISTANCE;
	objective[4].y = game->player->pos.y + MIN_DISTANCE;

	objective[5].x = game->player->pos.x - MIN_DISTANCE;
	objective[5].y = game->player->pos.y + MIN_DISTANCE;

	objective[6].x = game->player->pos.x - MIN_DISTANCE;
	objective[6].y = game->player->pos.y - MIN_DISTANCE ;

	objective[7].x = game->player->pos.x + MIN_DISTANCE;
	objective[7].y = game->player->pos.y - MIN_DISTANCE;

	fPoint ret;
	float dist = INFINITY;

	for (int i = 0; i < 8; ++i){
		float x = abs(objective[i].x - pos.x);
		float y = abs(objective[i].y - pos.x);
		float new_dist = sqrtf(powf(x, 2) + powf(y, 2));
		if (new_dist < dist) {
			ret = objective[i];
			dist = new_dist;
		}
	}

	return ret;
}


void EnemyLobber::LookAtPlayer(){

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

void EnemyLobber::Shot(){

	if (shot_timer.getTime() > RELOAD_TIME){
		ShotParticle();
		shot_timer.restart();
	}

}

void EnemyLobber::Continue(){
	/*float dist_x = abs(game->player->pos.x - pos.x);
	float dist_y = abs(game->player->pos.y - pos.y);

	float dist = sqrt(powf(dist_x, 2) + powf(dist_y, 2));

	bool run_away;
	if (dist >= MIN_DISTANCE) run_away = false;
	else run_away = true;*/

	fPoint objective = CalculateObjectivePosition();

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

void EnemyLobber::ShotParticle(){
	fPoint speed;
	if (current_anim == &a_up) {
		speed.x = 0;
		speed.y = -SHOT_SPEED / 6;
	}
	else if (current_anim == &a_right){
		speed.x = SHOT_SPEED / 6;
		speed.y = 0;
	}
	else if (current_anim == &a_up_right){
		speed.x = SHOT_SPEED / 6;
		speed.y = -SHOT_SPEED / 6;
	}
	else if (current_anim == &a_down){
		speed.x = 0;
		speed.y = SHOT_SPEED / 6;
	}
	else if (current_anim == &a_down_right){
		speed.x = SHOT_SPEED / 6;
		speed.y = SHOT_SPEED / 6;
	}
	else if (current_anim == &a_left){
		speed.x = -SHOT_SPEED / 6;
		speed.y = 0;
	}
	else if (current_anim == &a_up_left){
		speed.x = -SHOT_SPEED / 6;
		speed.y = -SHOT_SPEED / 6;
	}
	else if (current_anim == &a_down_left){
		speed.x = -SHOT_SPEED / 6;
		speed.y = SHOT_SPEED / 6;
	}

	game->particles->AddParticle(pos, speed, game->enemies->GetGraphics(), rock_particle,LOBBER_SHOT_COLLIDER, attack_fx);
}