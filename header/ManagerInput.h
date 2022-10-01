
#ifndef INCLUDE_GUARD_MANAGERINPUT_H
#define INCLUDE_GUARD_MANAGERINPUT_H


#include <SDL.h>
#include <vector>
#include <iostream>
#include <utility>

#include "GameSDL.h"
#include "Vector2D.h"


enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};


class ManagerInput {

public:
    static ManagerInput * Instance() {                                       // MAKING THIS CLASS AS "SINGLETON"
        if( s_pInstance == 0 ){                                                 // ONLY IF THERE IS ANY INSTANCE
            s_pInstance = new ManagerInput();                                // CREATE THE NEW INSTANCE
        }
        return s_pInstance;                                                     // IF NOT, RETURN THAT INSTANCE
    }

    void Update();																// THIS IS FOR "HANDLING EVENTS" IN THE GAME LAYER
	void Reset();
	void Clean();
    void Quit();

    void InitializeControllers();                                               // JOYSTICK FUNCTIONS
    bool JoysticksInitialised() { return m_bJoysticksInitialised; }             // FUNCTION WHICh RETURN THE JOYSTICK IS INITIALISED


    int Xvalue( int joy, int stick );                                           // PARAMETER joy IS THE IDENTIFIER(ID) OF THE JOYSTICK WE WANT 1,2 -> LEFT,RGHT STICK OF XBOX 360 CONTOLLER
    int Yvalue( int joy, int stick );


    /*
    bool getButtonState( int joy, int buttonNumber );

    bool getMouseButtonState( int buttonNumber );

    Vector2D * getMousePosition(){ return m_mousePosition; };
    */


    // keyboard events
    bool IsKeyDown(SDL_Scancode key) const;
	bool IsKeyUp(SDL_Scancode key) const;
	const Uint8* GetKeyState() const;


    // joystick events
    int GetAxisX(int joy, int stick) const;
    int GetAxisY(int joy, int stick) const;

    bool GetButtonState(int joy, int buttonNumber) const;

    // mouse events
    bool GetMouseButtonState(int buttonNumber) const;
    Vector2D* GetMousePosition() const;


private:

    ManagerInput();
    ~ManagerInput();

    static ManagerInput* s_pInstance;                                       // FOR INDICATING THE UNIQUE InputHandler Instance (SINGLETON PATTERN)

    std::vector<SDL_Joystick*> m_joysticks;                                     // TO STORE THE JOYSTICKS WHICH IS INITIALISED
    bool m_bJoysticksInitialised;

    std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;              // ONE Vector2D IS FOR JOYSTICKS, AND ANOTHER IS FOR AXISES MOVING NOW
    std::vector<std::vector<bool> > m_buttonStates;                              // FOR BUTTONS
    std::vector<bool> m_mouseButtonStates;                                      // FOR MOUSE

    Vector2D * m_mousePosition;                                                 // FOR MOUSE POSITION

    const int m_joystickDeadZone = 10000;                                       // SENSITIVITY OF MOVING STICK


    // keyboard specific
    // FOR KEYBOARD INPUT, WE DON'T NEED TO HAVE ENTIRE MAP TO OUR KEYBOARD
    const Uint8 * m_keystates;                                                   // THIS WILL BE USED TO GET THE RESULT RETURNED FROM "SDL_GetKeyboardState()"

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
};


typedef ManagerInput Instance_ManagerInput;



#endif
