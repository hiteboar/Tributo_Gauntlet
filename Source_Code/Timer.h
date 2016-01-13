#pragma once
#include "SDL\include\SDL.h"

class Timer {

private:
	float start_time;

public:
	Timer(){
		start_time = SDL_GetTicks();
	}

	float getTime(){
		float time = SDL_GetTicks();
		return time - start_time;
	}

	void restart(){
		start_time = SDL_GetTicks();
	}

};