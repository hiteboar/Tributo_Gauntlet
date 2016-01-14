#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"
#include "ModuleAudio.h"
#include "Particle.h"


ModulePlayer::ModulePlayer(){

	enable = false;

	up.frames.push_back({ 0, 108, TILE_WIDTH, TILE_HEIGHT });
	up.frames.push_back({ 0, 126, TILE_WIDTH, TILE_HEIGHT });
	up.frames.push_back({ 0, 144, TILE_WIDTH, TILE_HEIGHT });
	up.frames.push_back({ 0, 162, TILE_WIDTH, TILE_HEIGHT });
	up.loop = true;
	up.speed = 0.2;

	up_right.frames.push_back({ 18, 108, TILE_WIDTH, TILE_HEIGHT });
	up_right.frames.push_back({ 18, 126, TILE_WIDTH, TILE_HEIGHT });
	up_right.frames.push_back({ 18, 144, TILE_WIDTH, TILE_HEIGHT });
	up_right.frames.push_back({ 18, 162, TILE_WIDTH, TILE_HEIGHT });
	up_right.loop = true;
	up_right.speed = 0.2;

	right.frames.push_back({ 36, 108, TILE_WIDTH, TILE_HEIGHT });
	right.frames.push_back({ 36, 126, TILE_WIDTH, TILE_HEIGHT });
	right.frames.push_back({ 36, 144, TILE_WIDTH, TILE_HEIGHT });
	right.frames.push_back({ 36, 162, TILE_WIDTH, TILE_HEIGHT });
	right.loop = true;
	right.speed = 0.2;

	down_right.frames.push_back({ 54, 108, TILE_WIDTH, TILE_HEIGHT });
	down_right.frames.push_back({ 54, 126, TILE_WIDTH, TILE_HEIGHT });
	down_right.frames.push_back({ 54, 144, TILE_WIDTH, TILE_HEIGHT });
	down_right.frames.push_back({ 54, 162, TILE_WIDTH, TILE_HEIGHT });
	down_right.loop = true;
	down_right.speed = 0.2; 

	down.frames.push_back({ 72, 108, TILE_WIDTH, TILE_HEIGHT });
	down.frames.push_back({ 72, 126, TILE_WIDTH, TILE_HEIGHT });
	down.frames.push_back({ 72, 144, TILE_WIDTH, TILE_HEIGHT });
	down.frames.push_back({ 72, 162, TILE_WIDTH, TILE_HEIGHT });
	down.loop = true;
	down.speed = 0.2;

	down_left.frames.push_back({ 90, 108, TILE_WIDTH, TILE_HEIGHT });
	down_left.frames.push_back({ 90, 126, TILE_WIDTH, TILE_HEIGHT });
	down_left.frames.push_back({ 90, 144, TILE_WIDTH, TILE_HEIGHT });
	down_left.frames.push_back({ 90, 162, TILE_WIDTH, TILE_HEIGHT });
	down_left.loop = true;
	down_left.speed = 0.2;

	left.frames.push_back({ 108, 108, TILE_WIDTH, TILE_HEIGHT });
	left.frames.push_back({ 108, 126, TILE_WIDTH, TILE_HEIGHT });
	left.frames.push_back({ 108, 144, TILE_WIDTH, TILE_HEIGHT });
	left.frames.push_back({ 108, 162, TILE_WIDTH, TILE_HEIGHT });
	left.loop = true;
	left.speed = 0.2;

	up_left.frames.push_back({ 126, 108, TILE_WIDTH, TILE_HEIGHT });
	up_left.frames.push_back({ 126, 126, TILE_WIDTH, TILE_HEIGHT });
	up_left.frames.push_back({ 126, 144, TILE_WIDTH, TILE_HEIGHT });
	up_left.frames.push_back({ 126, 162, TILE_WIDTH, TILE_HEIGHT });
	up_left.loop = true;
	up_left.speed = 0.2;

	start.frames.push_back({ 252, 91, TILE_WIDTH, TILE_HEIGHT });
	start.frames.push_back({ 252, 109, TILE_WIDTH, TILE_HEIGHT });
	start.frames.push_back({ 252, 127, TILE_WIDTH, TILE_HEIGHT });
	start.frames.push_back({ 252, 145, TILE_WIDTH, TILE_HEIGHT });
	start.frames.push_back({ 252, 163, TILE_WIDTH, TILE_HEIGHT });
	start.frames.push_back({ 252, 181, TILE_WIDTH, TILE_HEIGHT });
	start.loop = false;
	start.speed = 0.8;

	/// 8 dispars diferents
	shot_up.x = 180; shot_up.y = 0; shot_up.w = TILE_WIDTH; shot_up.h = TILE_HEIGHT;

	shot_up_right.x = 180; shot_up_right.y = 18; shot_up_right.w = TILE_WIDTH; shot_up_right.h = TILE_HEIGHT;

	shot_right.x = 180; shot_right.y = 36; shot_right.w = TILE_WIDTH; shot_right.h = TILE_HEIGHT;

	shot_down_right.x = 180; shot_down_right.y = 54; shot_down_right.w = TILE_WIDTH; shot_down_right.h = TILE_HEIGHT;

	shot_down.x = 180; shot_down.y = 72; shot_down.w = TILE_WIDTH; shot_down.h = TILE_HEIGHT;

	shot_down_left.x = 180; shot_down_left.y = 90; shot_down_left.w = TILE_WIDTH; shot_down_left.h = TILE_HEIGHT;

	shot_left.x = 180; shot_left.y = 108; shot_left.w = TILE_WIDTH; shot_left.h = TILE_HEIGHT;

	shot_up_left.x = 180; shot_up_left.y = 126; shot_up_left.w = TILE_WIDTH; shot_up_left.h = TILE_HEIGHT;


	mov_flag = 0;
}


ModulePlayer::~ModulePlayer(){
}

bool ModulePlayer::Init(){
	pos.x = TILE_WIDTH * 2;
	pos.y = TILE_HEIGHT * 2;

	return true;
}

bool ModulePlayer::Start(){
	graphics = game->textures->Load(HEROESFILE_PATH);
	current_anim = &right;

	SDL_Rect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = TILE_WIDTH;
	rect.h = TILE_HEIGHT;
	collider = game->collider->AddCollider(rect, PLAYER_COLLIDER, this);


	game->particles->AddParticle(pos, { 0, 0 }, graphics, start, NO_COLLIDER);

	playerAttack_fx =  game->audio->LoadFx("Audio/PlayerAttack.wav");

	return true;
}

bool ModulePlayer::PreUpdate(){

	if (game->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && !shot) {
		ShotParticle();
		game->audio->PlayFx(playerAttack_fx);
		shot = true;
	}

	if (game->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) mov_flag |= UP; 
	else if (game->input->GetKey(SDL_SCANCODE_W) == KEY_UP) mov_flag &= BLOCK_UP;

	if (game->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) mov_flag |= RIGHT;
	else if (game->input->GetKey(SDL_SCANCODE_D) == KEY_UP) mov_flag &= BLOCK_RIGHT;

	if (game->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) mov_flag |= DOWN; 
	else if (game->input->GetKey(SDL_SCANCODE_S) == KEY_UP) mov_flag &= BLOCK_DOWN; 

	if (game->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) mov_flag |= LEFT; 
	else if (game->input->GetKey(SDL_SCANCODE_A) == KEY_UP) mov_flag &= BLOCK_LEFT;

	switch (mov_flag){
	case UP:
		current_anim = &up;
		current_anim->stop = false;
		break;
	case RIGHT: 
		current_anim = &right;
		current_anim->stop = false;
		break;
	case UP_RIGHT:
		current_anim = &up_right;
		current_anim->stop = false;
		break;
	case DOWN:
		current_anim = &down;
		current_anim->stop = false;
		break;
	case DOWN_RIGHT:
		current_anim = &down_right;
		current_anim->stop = false;
		break;
	case LEFT:
		current_anim = &left;
		current_anim->stop = false;
		break;
	case UP_LEFT:
		current_anim = &up_left; 
		current_anim->stop = false;
		break;
	case DOWN_LEFT:
		current_anim = &down_left;
		current_anim->stop = false;
		break;

	default: //idle anim
		current_anim->stop = true;
		break;
	}

	return true;
}

bool ModulePlayer::Update(){

	if (!current_anim->stop){

		if ((mov_flag & RIGHT) == RIGHT) pos.x += speed;
		if ((mov_flag & LEFT) == LEFT) pos.x -= speed;
		if ((mov_flag & DOWN) == DOWN) pos.y += speed;
		if ((mov_flag & UP) == UP) pos.y -= speed;

	}

	collider->rect.x = pos.x;
	collider->rect.y = pos.y;

	game->renderer->Blit(graphics, pos.x, pos.y, &(current_anim->GetCurrentFrame()));

	return true;
}


void ModulePlayer::ShotParticle(){
	fPoint speed;
	Animation anim;
	if (current_anim == &up) {
		speed.x = 0;
		speed.y = -SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_up);
	}
	else if (current_anim == &right){
		speed.x = SHOT_SPEED * 1.5;
		speed.y = 0;
		anim.frames.push_back(shot_right);
	}
	else if (current_anim == &up_right){
		speed.x = SHOT_SPEED * 1.5;
		speed.y = -SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_up_right);
	}
	else if (current_anim == &down){
		speed.x = 0;
		speed.y = SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_down);
	}
	else if (current_anim == &down_right){
		speed.x = SHOT_SPEED * 1.5;
		speed.y = SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_down_right);
	}
	else if (current_anim == &left){
		speed.x = -SHOT_SPEED * 1.5;
		speed.y = 0;
		anim.frames.push_back(shot_left);
	}
	else if (current_anim == &up_left){
		speed.x = -SHOT_SPEED * 1.5;
		speed.y = -SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_up_left);
	}
	else if (current_anim == &down_left){
		speed.x = -SHOT_SPEED * 1.5;
		speed.y = SHOT_SPEED * 1.5;
		anim.frames.push_back(shot_down_left);
	}

	game->particles->AddParticle(pos, speed, graphics, anim, PLAYER_SHOT_COLLIDER);
}

void ModulePlayer::OnCollision(Collider* a, Collider* b){

	if (b->type == LOBBER_SHOT_COLLIDER 
		|| b->type == DEMON_SHOT_COLLIDER
		|| b->type == GRUNT_ATTACK_COLLIDER
		|| b->type == SORCERER_ATTACK_COLLIDER){
		switch (b->type){
		case LOBBER_SHOT_COLLIDER:
			Hit(LOBBER);
			break;
		case DEMON_SHOT_COLLIDER:
			Hit(DEMON);
			break;
		case GRUNT_ATTACK_COLLIDER:
			Hit(GRUNT);
			break;
		case SORCERER_ATTACK_COLLIDER:
			Hit(SORCERER);
			break;
		}
	}
	else { 
		double center_ax = a->rect.x + a->rect.w/2;
		double center_ay = a->rect.y + a->rect.h/2;

		double center_bx = b->rect.x + b->rect.w/2;
		double center_by = b->rect.y + b->rect.h/2;

		double vector_x = center_bx - center_ax;
		double vector_y = center_by - center_ay;

		double vector_dir = sqrt(pow(vector_x, 2) + pow(vector_y, 2));

		double angle = acos(vector_x / vector_dir);


		if (angle < M_PI / 4 || angle > 7 * M_PI / 4) mov_flag &= BLOCK_RIGHT;
		else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4) mov_flag &= BLOCK_LEFT;
		else{
			if (center_ay > center_by) mov_flag &= BLOCK_UP;
			else if (center_ay < center_by) mov_flag &= BLOCK_DOWN;
		}

	}
}


void ModulePlayer::Hit(enemy_type enemy){
	switch (enemy){
	case GHOST:
		health -= 30;
		break;
	case DEMON:
		health -= 20;
		break;
	case SORCERER:
		health -= 20;
		break;
	case LOBBER:
		health -= 10;
		break;
	case GRUNT:
		health -= 10;
		break;
	}
}

bool ModulePlayer::CleanUp(){
	game->textures->Unload(graphics);
	return true;
}