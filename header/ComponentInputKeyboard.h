#ifndef INCLUDE_GUARD_COMPOMENTINPUTKEYBOARD_H
#define INCLUDE_GUARD_COMPOMENTINPUTKEYBOARD_H

#include <SDL.h>

#include "GameSDL.h"
#include "ManagerEntity.h"
#include "ManagerInput.h"


class ComponentTransform;

class ComponentInputKeyboard: public Component {
public:

        
	ComponentInputKeyboard();
	ComponentInputKeyboard( 	SDL_Scancode upKey, 
								SDL_Scancode rightKey, 
								SDL_Scancode downKey, 
								SDL_Scancode leftKey, 
								SDL_Scancode writeKey);

	void Initialize();
	void Update();


	bool Key_Up;
	bool Key_Down;
	bool Key_Right;
	bool Key_Left;
	bool Key_Write;


private:
	SDL_Scancode m_Key_up;
    SDL_Scancode m_Key_down;
    SDL_Scancode m_Key_right;
    SDL_Scancode m_Key_left;
    SDL_Scancode m_Key_write;




};

#endif
