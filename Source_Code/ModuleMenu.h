#ifndef __MODULEMENU_H__
#define __MODULEMENU_H__

#include "Module.h"
#include "Globals.h"
#include "Timer.h"
#include <string>

using namespace std;

struct SDL_Texture;

class ModuleMenu : public Module {


public:

	bool enable = true;

	ModuleMenu();
	~ModuleMenu();

	bool Init();
	bool Start();
	bool Update();
	bool CleanUp();

	void Success();
private:

	int score = 0;
	int health = 0;

	SDL_Rect menu;
	SDL_Rect coin;
	SDL_Rect game_over;
	SDL_Rect success;

	SDL_Rect one;
	SDL_Rect two;
	SDL_Rect three;
	SDL_Rect four;
	SDL_Rect five;
	SDL_Rect six;
	SDL_Rect seven;
	SDL_Rect eight;
	SDL_Rect nine;
	SDL_Rect zero;

	Timer time; 
	bool start = false;

	void DrawInt(int number, int x, int y); 
	SDL_Rect* SelectNum(char num);
	void DrawSuccess();
	void DrawGameOver();

	bool GAME_OVER = false;
	bool SUCCESS = false;

#define BLINK 500

	SDL_Texture* graphics;
	int coin_fx, welcome_fx, die_fx, success_fx;
};

#endif // __MODULEMENU_H__