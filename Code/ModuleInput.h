#ifndef __INPUTMODULE_H__
#define __INPUTMODULE_H__

#include "Module.h"

#include "SDL/include/SDL_scancode.h"

enum KeyState{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

class ModuleInput : public Module {

public:

	ModuleInput();

	~ModuleInput();

	bool Init();

	bool Start();

	bool PreUpdate();

	bool CleanUp();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	/*KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}*/

	bool GetWindowEvent(EventWindow code) const;

	//const iPoint& GetMouseMotion() const;
	//const iPoint& GetMousePosition() const;

private:

	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
};

#endif //__INPUTMODULE_H__