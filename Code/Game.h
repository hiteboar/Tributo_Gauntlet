#ifndef  __GAME_H
#define __GAME_H

#include <list>
#include "Module.h"
#include "Timer.h"

class ModuleWindow;
class ModuleRender;
class ModuleInput;
class ModuleMap;
class ModuleTextures;
class ModulePlayer;
class ModuleCollision;
class ModuleParticles;
class ModuleEnemy;
class ModuleMenu;
class ModuleAudio;

class Game{

public:

	ModuleWindow* window;
	ModuleRender* renderer;
	ModuleInput* input;
	ModuleMap* map;
	ModuleTextures* textures;
	ModulePlayer* player;
	ModuleCollision* collider; 
	ModuleParticles* particles;
	ModuleEnemy* enemies;
	ModuleMenu* menu; 
	ModuleAudio* audio;
public:
	Game();
	~Game();

	bool Start();
	bool Update();
	bool CleanUp();

	void EnableModules();
	void DisableModules();
	void Restart();

private:

	std::list<Module*> modules;
	Timer time;
};

extern Game* game;

#endif //  __GAME_H



