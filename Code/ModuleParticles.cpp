#include "ModuleParticles.h"
#include "Particle.h"
#include "Game.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Game.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Globals.h"

ModuleParticles::ModuleParticles(){
	enable = false;
}

ModuleParticles::~ModuleParticles(){
	/*list<Particle* >::iterator it = particles.begin();

	for (it; it != particles.end(); ++it){
		delete *it;
	}*/
}

bool ModuleParticles::Start(){
	graphics = game->textures->Load(HEROESFILE_PATH);

	impact.frames.push_back({ 234, 91, TILE_WIDTH, TILE_HEIGHT });
	impact.frames.push_back({ 234, 109, TILE_WIDTH, TILE_HEIGHT });
	impact.frames.push_back({ 234, 127, TILE_WIDTH, TILE_HEIGHT });
	impact.frames.push_back({ 234, 145, TILE_WIDTH, TILE_HEIGHT });
	impact.loop = false;
	impact.speed = 2;
	
	return true;
}



bool ModuleParticles::PreUpdate(){
	list<Particle* >::iterator it = particles.begin();
	while (it != particles.end()){
		if ((*it)->destroy) {
			RELEASE(*it);
			it = particles.erase(it);
		}
		else ++it;
	}
	return true;
}

bool ModuleParticles::Update(){
	list<Particle* >::iterator it;
	for (it = particles.begin(); it != particles.end(); ++it){
		game->renderer->Blit((*it)->tex, (*it)->pos.x, (*it)->pos.y, &((*it)->anim.GetCurrentFrame()));
	}
	return true;
}

bool ModuleParticles::PostUpdate(){
	list<Particle* >::iterator it;
	for (it = particles.begin(); it != particles.end(); ++it){
		(*it)->Move();

		int y = abs(game->player->pos.y - (*it)->pos.y);
		int x = abs(game->player->pos.x - (*it)->pos.x);

		if (((*it)->anim.loop == false && (*it)->anim.Finished())
			|| (x >  SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT * 2 / 3)){
			(*it)->destroy = true;
			if ((*it)->collider != nullptr) (*it)->collider->to_delete = true;
		}
	}
	return true;
}

bool ModuleParticles::CleanUp(){
	list<Particle* >::iterator it = particles.begin();
	for (it; it != particles.end(); ++it) RELEASE(*it);
	particles.clear();
	return true;
}

void ModuleParticles::AddParticle(fPoint pos, fPoint speed, SDL_Texture* tex, Animation animation,  collider_type c_type, int sound){
	Particle* particle = new Particle (pos, speed, tex, animation, sound);
	SDL_Rect rect;
	rect.x = particle->pos.x;
	rect.y = particle->pos.y;
	rect.w = TILE_WIDTH;
	rect.h = TILE_HEIGHT;

	if (c_type != NO_COLLIDER){
		Collider* collider = game->collider->AddCollider(rect, c_type, this);
		particle->AddCollider(collider);
	}

	particles.push_back(particle);
}

void ModuleParticles::OnCollision(Collider* a, Collider* b){
	list<Particle* >::iterator it = particles.begin();
	bool exit = false;
	bool destroy = true;

	if (a->type == PLAYER_SHOT_COLLIDER && b->type == ENEMY_COLLIDER){
		Enemy* enemy = game->enemies->GetEnemy(b);
		if (enemy != nullptr && enemy->invisible) destroy = false;
	}

	while (it != particles.end() && !exit && destroy){

		if ((*it)->collider == a){
			if (a->type != GRUNT_ATTACK_COLLIDER && a->type != SORCERER_ATTACK_COLLIDER){
				(*it)->destroy = true;
				game->particles->AddParticle((*it)->pos, { 0, 0 }, graphics, impact, NO_COLLIDER);
			}
			if (!(*it)->destroy) (*it)->collider = nullptr;
			game->audio->PlayFx((*it)->sound_fx);
			exit = true;
		}

		else ++it;
	}

	a->to_delete = destroy;

}