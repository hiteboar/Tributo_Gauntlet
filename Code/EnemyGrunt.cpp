#include "EnemyGrunt.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

EnemyGrunt::EnemyGrunt(int health, int x, int y, Module* module) : Enemy(health, x, y, module, GRUNT){

	a_up.frames.push_back({ 144, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up.frames.push_back({ 144, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up.loop = true;
	a_up.speed = 0.2;

	a_up_right.frames.push_back({ 162, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.frames.push_back({ 162, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up_right.loop = true;
	a_up_right.speed = 0.2;

	a_right.frames.push_back({ 180, 0, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 18, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 36, TILE_WIDTH, TILE_HEIGHT });
	a_right.frames.push_back({ 180, 54, TILE_WIDTH, TILE_HEIGHT });
	a_right.loop = true;
	a_right.speed = 0.2;

	a_down_right.frames.push_back({ 198, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.frames.push_back({ 198, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down_right.loop = true;
	a_down_right.speed = 0.2;

	a_down.frames.push_back({ 216, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down.frames.push_back({ 216, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down.loop = true;
	a_down.speed = 0.2;

	a_down_left.frames.push_back({ 234, 0, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 18, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 36, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.frames.push_back({ 234, 54, TILE_WIDTH, TILE_HEIGHT });
	a_down_left.loop = true;
	a_down_left.speed = 0.2;

	a_left.frames.push_back({ 252, 0, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 18, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 36, TILE_WIDTH, TILE_HEIGHT });
	a_left.frames.push_back({ 252, 54, TILE_WIDTH, TILE_HEIGHT });
	a_left.loop = true;
	a_left.speed = 0.2;

	a_up_left.frames.push_back({ 270, 0, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 18, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 36, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.frames.push_back({ 270, 54, TILE_WIDTH, TILE_HEIGHT });
	a_up_left.loop = true;
	a_up_left.speed = 0.2;

	attack.frames.push_back({ 216, 144, TILE_WIDTH, TILE_HEIGHT});
	attack.frames.push_back({ 216, 144, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 216, 144, TILE_WIDTH, TILE_HEIGHT });
	attack.frames.push_back({ 216, 144, TILE_WIDTH, TILE_HEIGHT });
	attack.loop = false;
	attack.speed = 0.8;

	attack_fx = game->audio->LoadFx("Audio/GruntAttack.wav");
}

fPoint EnemyGrunt::CalculateObjectivePosition(){
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


void EnemyGrunt::LookAtPlayer(){

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

void EnemyGrunt::Attack(){

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

		game->particles->AddParticle(attack_pos, { 0, 0 }, game->enemies->GetGraphics(), attack, GRUNT_ATTACK_COLLIDER, attack_fx);
		attack_time.restart();
	}
	

}

void EnemyGrunt::Continue(){

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