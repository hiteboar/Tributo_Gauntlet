#include "Game.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"  
#include "ModuleMap.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"
#include "ModuleMenu.h"
#include "ModuleAudio.h"

 Game::Game(){
	 modules.push_back(input = new ModuleInput());
	 modules.push_back(window = new ModuleWindow());
	 modules.push_back(textures = new ModuleTextures());
	 modules.push_back(map = new ModuleMap());
	 modules.push_back(collider = new ModuleCollision());
	 modules.push_back(player = new ModulePlayer());
	 modules.push_back(enemies = new ModuleEnemy());
	 modules.push_back(particles = new ModuleParticles());
	 modules.push_back(menu = new ModuleMenu());
	 modules.push_back(audio = new ModuleAudio());
	 modules.push_back(renderer = new ModuleRender());
}

 Game::~Game(){
	 std::list<Module*>::iterator it;

	 for (it = modules.begin(); it != modules.end(); ++it){
		 delete *it;
	 }

 }

 bool Game::Start(){
	 bool ret = true;

	 std::list<Module*>::iterator it;
	 for (it = modules.begin(); it != modules.end() && ret; ++it){
		 ret = (*it)->Init();
	 }

	 for (it = modules.begin(); it != modules.end() && ret; ++it){
		 ret = (*it)->Start();
	 }

	 return ret;
 }

 bool Game::Update(){
	 bool ret = true;
	 std::list<Module*>::iterator it;

	 if (time.getTime() >= 1000 / FPS){

		 for (it = modules.begin(); it != modules.end() && ret; ++it){
			 if ((*it)->enable) ret = (*it)->PreUpdate();
		 }

		 for (it = modules.begin(); it != modules.end() && ret; ++it){
			 if ((*it)->enable) ret = (*it)->Update();
		 }

		 for (it = modules.begin(); it != modules.end() && ret; ++it){
			 if ((*it)->enable) ret = (*it)->PostUpdate();
		 }

		 time.restart();
	 }
	 return ret;
 }

 bool Game::CleanUp(){
	 bool ret = true;
	 std::list<Module*>::iterator it;

	 for (it = modules.begin(); it != modules.end() && ret; ++it){
		 ret &= (*it)->CleanUp();
	 }
	 return ret;
 }

 void Game::EnableModules(){
	 player->enable = true;
	 enemies->enable = true;
	 particles->enable = true;
 }

 void Game::DisableModules(){
	 player->enable = false;
	 enemies->enable = false;
	 particles->enable = false;
 }

 void Game::Restart(){

	 player->CleanUp();
	 enemies->CleanUp();
	 particles->CleanUp();
	 collider->CleanUp();
	 map->CleanUp();


	 map->Init();
	 collider->Init();
	 player->Init();
	 enemies->Init();
	 particles->Init();

	 map->Start();
	 collider->Start();
	 player->Start();
	 enemies->Start();
	 particles->Start();
 }

