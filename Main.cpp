#include <stdlib.h>
#include "Globals.h"
#include "Game.h"
//#include "vld.h"

#include "SDL\include\SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Game* game = nullptr; 

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states  state = MAIN_CREATION;

	while (state != MAIN_EXIT){
		switch (state){
		case MAIN_CREATION:
			game = new Game();
			state = MAIN_START;
			break;
		case MAIN_START:
			if (game->Start()) state = MAIN_UPDATE;
			else state = MAIN_FINISH;
			break;
		case MAIN_UPDATE:
			if (!game->Update()) state = MAIN_FINISH;
			break;
		case MAIN_FINISH:
			if(game->CleanUp()) main_return = EXIT_SUCCESS;
			state = MAIN_EXIT;
			break;
		}

	}

	delete game;

	return main_return;
}