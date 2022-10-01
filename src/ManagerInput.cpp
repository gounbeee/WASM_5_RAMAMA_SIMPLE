
#include <ManagerInput.h>
#include <typeinfo>



extern "C" {



ManagerInput* ManagerInput::s_pInstance = 0;


// CONSTRUCTOR
ManagerInput::ManagerInput():		m_keystates(0),
									m_bJoysticksInitialised(false),
									m_mousePosition(new Vector2D(0,0)) {

	std::cout << "InputController::InputController() -- CONSTRUCTOR CALLED" << std::endl;

    for ( int i = 0; i < 3; i++ ){
        m_mouseButtonStates.push_back(false);
    }

}


// DESTRUCTOR
ManagerInput::~ManagerInput() {

	std::cout << "InputController::~InputController() -- DESTRUCTOR CALLED" << std::endl;

    // delete anything we created dynamically
    delete m_keystates;
    delete m_mousePosition;

    // clear our arrays
    m_joystickValues.clear();
    m_joysticks.clear();
    m_buttonStates.clear();
    m_mouseButtonStates.clear();
}


// PUBLIC FUNCTIONS
void ManagerInput::InitializeControllers() {
    if( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 ){                                    // CHECKING JOYSTICK SUBSYSTEM IS INITIALISED, THEN IF NOT,
        SDL_InitSubSystem( SDL_INIT_JOYSTICK );                                     // INITIALISE THE SUBSYSTEM FIRST
    }

    if( SDL_NumJoysticks() > 0 ){                                                   // IF THERE ARE AN AVAILABLE JOYSTICKS ARE FOUND,
        for( int i = 0; i < SDL_NumJoysticks(); i++ ){
            SDL_Joystick* joy = SDL_JoystickOpen(i);                                // OPENING THE JOYSTICK USING SDL LIBRARY

            if ( SDL_JoystickOpen(i) ){                                             // IF THERE IS OPENED JOYSTICK
                m_joysticks.push_back( joy );
                m_joystickValues.push_back( std::make_pair( new Vector2D(0,0), new Vector2D(0,0)) );      // STORE THAT TO vector


                std::vector<bool> tempButtons;

                for( int j = 0; j < SDL_JoystickNumButtons( joy ); j++ ){           // GETTING NUMBER OF BUTTONS FOR EACH OF OUR JOYSTICKS
                    tempButtons.push_back( false );                                 // 'false' MEANS "NOT-PRESSED" SO WE FIRST PUSH THESE VALUES
                                                                                    // BECAUSE WE USE push_back() SO THE COUNT OF FALSE WILL BE SAME AS THE NUMBER OF BUTTON
                }

                m_buttonStates.push_back( tempButtons );                            // push the button array into the button state array


            } else {                                                                // OR NOT,
                std::cout << SDL_GetError();                                        // PRINT OUT 'SDL_ERROR'
            }
        }

        SDL_JoystickEventState( SDL_ENABLE );                                       // ENABLING TO START EVENTS FROM THE JOYSTICKS
        m_bJoysticksInitialised = true;                                             // FLAG TO "ON"

        std::cout << "InputController::InitializeControllers() -- " << m_joysticks.size() << " joystick(s)" << std::endl;

    } else {                                                                        // THERE ARE NO JOYSTICKS
		std::cout << "InputController::InitializeControllers() -- THERE IS NO JOYSTICS" << std::endl;
        m_bJoysticksInitialised = false;                                            // FLAG TO "OFF"
    }

}


void ManagerInput::Clean() {
    if( m_bJoysticksInitialised ) {                                                 // WHEN CLEAN UP THE JOYSTICKS
        for ( unsigned int i = 0; i < SDL_NumJoysticks(); i++ ){                    // LOOP TO EVERY JOYSTICKS IN THE vector STORING THE JOYSTICKS WE HAVE
            SDL_JoystickClose( m_joysticks[i] );                                    // CLOSE THAT
        }
    }
}


void ManagerInput::Quit() {

	Clean();
	//delete s_pInstance;
}


void ManagerInput::Reset() {
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[RIGHT] = false;
    m_mouseButtonStates[MIDDLE] = false;
}



void ManagerInput::Update() {                                                    // THIS IS SO CALLED "EVENT LOOP"

    SDL_Event event;                                                                // MAKING NEW EVENT OBJECT TO GET

    /*
    while( SDL_PollEvent( &event )){                                                // FOR EVERY EVENTS WE GOT,

        if( event.type == SDL_QUIT ){                                               // IF THE EVENT IS FOR 'QUIT'
            TheGame::Instance()->quit();                                            // RUN THE FUNCTION TO QUIT THE APPLICATION
            TheGame::Instance()->clean();                                           // TODO:: QUITTING GAME PROCESS ************
        }


        if(event.type == SDL_JOYAXISMOTION) {                                       // GETTING THE INFORMATION ABOUT 'ANALOG JOYSTICK' EVENT
            int whichOne = event.jaxis.which;                                       // get which controller

            // event.jaxis.axis
            // 0 or 1 :: LEFT STICK
            // 3 or 4 :: RIGHT STICK
            if( event.jaxis.axis == 0 ) {                                           // LEFT STICK MOVING LEFT OR RIGHT
                if( event.jaxis.value > m_joystickDeadZone ){
                    m_joystickValues[ whichOne ].first->setX(1);
                } else if( event.jaxis.value < -m_joystickDeadZone ) {
                    m_joystickValues[ whichOne ].first->setX(-1);
                } else {
                    m_joystickValues[ whichOne ].first->setX(0);
                }
            }


            if( event.jaxis.axis == 1 ) {                                           // LEFT STICK MOVING UP OR DOWN
                if( event.jaxis.value > m_joystickDeadZone ){
                    m_joystickValues[ whichOne ].first->setY(1);
                } else if( event.jaxis.value < -m_joystickDeadZone ) {
                    m_joystickValues[ whichOne ].first->setY(-1);
                } else {
                    m_joystickValues[ whichOne ].first->setY(0);
                }
            }


            if( event.jaxis.axis == 3 ) {                                           // RIGHT STICK MOVING LEFT OR RIGHT
                if( event.jaxis.value > m_joystickDeadZone ){
                    m_joystickValues[ whichOne ].second->setX(1);
                } else if( event.jaxis.value < -m_joystickDeadZone ) {
                    m_joystickValues[ whichOne ].second->setX(-1);
                } else {
                    m_joystickValues[ whichOne ].second->setX(0);
                }
            }


            if( event.jaxis.axis == 4 ) {                                           // RIGHT STICK MOVING UP OR DOWN
                if( event.jaxis.value > m_joystickDeadZone ){
                    m_joystickValues[ whichOne ].second->setY(1);
                } else if( event.jaxis.value < -m_joystickDeadZone ) {
                    m_joystickValues[ whichOne ].second->setY(-1);
                } else {
                    m_joystickValues[ whichOne ].second->setY(0);
                }
            }

        }       // END OF ANALOG JOYSTICK



        if( event.type == SDL_JOYBUTTONDOWN ) {                                     // JOYSTICK BUTTON EVENT    // SDL_JOYBUTTONDOWN MEANS "PRESSED"
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
        }

        if( event.type == SDL_JOYBUTTONUP ) {                                       // JOYSTICK BUTTON EVENT    // SDL_JOYBUTTONDOWN MEANS "RELEASED"
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
        }



        if( event.type == SDL_MOUSEBUTTONDOWN ){                                    // MOUSE BUTTON EVENT
            if( event.button.button == SDL_BUTTON_LEFT ){
                m_mouseButtonStates[LEFT] = true;
            }

            if( event.button.button == SDL_BUTTON_MIDDLE ){
                m_mouseButtonStates[ MIDDLE ] = true;
            }

            if( event.button.button == SDL_BUTTON_RIGHT ){
                m_mouseButtonStates[ RIGHT ] = true;
            }
        }


        if( event.type == SDL_MOUSEBUTTONUP ){                                      // MOUSE BUTTON EVENT
            if( event.button.button == SDL_BUTTON_LEFT ){
                m_mouseButtonStates[LEFT] = false;
            }

            if( event.button.button == SDL_BUTTON_MIDDLE ){
                m_mouseButtonStates[ MIDDLE ] = false;
            }

            if( event.button.button == SDL_BUTTON_RIGHT ){
                m_mouseButtonStates[ RIGHT ] = false;
            }
        }


        if( event.type == SDL_MOUSEMOTION ){                                        // MOUSE MOVEMENT EVENT
            m_mousePosition->setX( event.motion.x );
            m_mousePosition->setY( event.motion.y );

        }
    }
    */

    while( SDL_PollEvent( &event ) ) {                                               // FOR EVERY EVENTS WE GOT,
		
		// ROUTING BETWEEN HARDWARES ( KEYBOARD, MOUSE, JOYSTICK )
        switch ( event.type )
        {
            case SDL_QUIT:
                //std::cout << "     ----- InputController::Update() -- SDL_QUIT OCCURED\n";
                //Instance_GameSDL::Instance()->Quit();
                break;

            case SDL_JOYAXISMOTION:
                //std::cout << "     ----- InputController::Update() -- SDL_JOYAXISMOTION OCCURED\n";
                onJoystickAxisMove(event);
                break;

            case SDL_JOYBUTTONDOWN:
                //std::cout << "     ----- InputController::Update() -- SDL_JOYBUTTONDOWN OCCURED\n";
                onJoystickButtonDown(event);
                break;

            case SDL_JOYBUTTONUP:
                //std::cout << "     ----- InputController::Update() -- SDL_JOYBUTTONUP OCCURED\n";
                onJoystickButtonUp(event);
                break;

            case SDL_MOUSEMOTION:
                //std::cout << "     ----- InputController::Update() -- SDL_MOUSEMOTION OCCURED\n";
                onMouseMove(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                //std::cout << "     ----- InputController::Update() -- SDL_MOUSEBUTTONDOWN OCCURED\n";
                onMouseButtonDown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                //std::cout << "     ----- InputController::Update() -- SDL_MOUSEBUTTONUP OCCURED\n";
                onMouseButtonUp(event);
                break;

            case SDL_KEYDOWN:
                //std::cout << "     ----- InputController::Update() -- SDL_KEYDOWN OCCURED\n";
                onKeyDown();
                break;

            case SDL_KEYUP:
                //std::cout << "     ----- InputController::Update() -- SDL_KEYUP OCCURED\n";
                onKeyUp();
                break;

            default:
                break;
        }
    }
}



int ManagerInput::Xvalue( int joy, int stick ){
    if( m_joystickValues.size() > 0 ){
        if( stick == 1 ) {
            return m_joystickValues[ joy ].first->getX();
        } else if( stick == 2 ) {
            return m_joystickValues[ joy ].second->getX();
        }
    }
    return 0;
}


int ManagerInput::Yvalue( int joy, int stick ){
    if( m_joystickValues.size() > 0 ){
        if( stick == 1 ) {
            return m_joystickValues[ joy ].first->getY();
        } else if( stick == 2 ) {
            return m_joystickValues[ joy ].second->getY();
        }
    }
    return 0;
}



bool ManagerInput::GetButtonState( int joy, int buttonNumber ) const {              // FIRST PARAMETER IS THE ID OF JOYSTICK , SECOND IS THE INDEX OF BUTTON
    return m_buttonStates[ joy ][ buttonNumber ];
}


bool ManagerInput::GetMouseButtonState( int buttonNumber ) const {
    return m_mouseButtonStates[ buttonNumber ];
}


const Uint8* ManagerInput::GetKeyState() const {
	if( m_keystates != 0 ) {
		return m_keystates;
    }
}


bool ManagerInput::IsKeyDown(SDL_Scancode key) const {                              // CHECKS WHETHER A KEY IS DOWN OR NOT

    // TO CHECK THE KEY NAME FROM SCANCODE
    // https://wiki.libsdl.org/SDL_GetKeyName
    //std::cout << SDL_GetKeyName( SDL_GetKeyFromScancode(key) ) << "\n";

    if(m_keystates != 0){
        if(m_keystates[ key ] == 1){
            return true;
        } else {
            return false;
        }
    }
    return false;
}


bool ManagerInput::IsKeyUp(SDL_Scancode key) const {                              // CHECKS WHETHER A KEY IS DOWN OR NOT

    // TO CHECK THE KEY NAME FROM SCANCODE
    // https://wiki.libsdl.org/SDL_GetKeyName
    //std::cout << SDL_GetKeyName( SDL_GetKeyFromScancode(key) ) << "\n";

    if(m_keystates != 0){
        if(m_keystates[ key ] == 0){
            return true;
        } else {
            return false;
        }
    }
    return false;
}



Vector2D* ManagerInput::GetMousePosition() const {
    return m_mousePosition;
}



int ManagerInput::GetAxisX(int joy, int stick) const {							// JOYSTICK EVENT HANDLERS
    if(m_joystickValues.size() > 0){
        if(stick == 1){
            return m_joystickValues[joy].first->getX();
        } else if(stick == 2) {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}


int ManagerInput::GetAxisY(int joy, int stick) const {
    if(m_joystickValues.size() > 0){
        if(stick == 1){
            return m_joystickValues[joy].first->getY();
        } else if(stick == 2){
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}


// PRIVATE FUNCTIONS
void ManagerInput::onKeyDown(){

    //std::cout << "typeid(m_keystates).name() ---  " << typeid(*m_keystates).name() << std::endl;
    m_keystates = SDL_GetKeyboardState(0);                                          // const Uint8* SDL_GetKeyboardState(int* numkeys)

}



void ManagerInput::onKeyUp(){
    m_keystates = SDL_GetKeyboardState(0);
}



// MOUSE EVENT HANDLERS
void ManagerInput::onMouseMove( SDL_Event &event ){
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
    std::cout << "MOUSE X:  " << event.motion.x << "  MOUSE Y:  " << event.motion.y << "\n";
}


void ManagerInput::onMouseButtonDown( SDL_Event &event ){
    if(event.button.button == SDL_BUTTON_LEFT){
        m_mouseButtonStates[LEFT] = true;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        m_mouseButtonStates[MIDDLE] = true;
    }

    if(event.button.button == SDL_BUTTON_RIGHT){
        m_mouseButtonStates[RIGHT] = true;
    }
}


void ManagerInput::onMouseButtonUp( SDL_Event &event ){
    if(event.button.button == SDL_BUTTON_LEFT){
        m_mouseButtonStates[LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE){
        m_mouseButtonStates[MIDDLE] = false;
    }

    if(event.button.button == SDL_BUTTON_RIGHT){
        m_mouseButtonStates[RIGHT] = false;
    }
}



void ManagerInput::onJoystickAxisMove( SDL_Event &event ){
    int whichOne = event.jaxis.which;

    // left stick move left or right
    if(event.jaxis.axis == 0){
        if (event.jaxis.value > m_joystickDeadZone){

            m_joystickValues[whichOne].first->setX(1);

        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(-1);
        } else {
            m_joystickValues[whichOne].first->setX(0);
        }
    }

    // left stick move up or down
    if(event.jaxis.axis == 1){
        if (event.jaxis.value > m_joystickDeadZone){

            m_joystickValues[whichOne].first->setY(1);

        } else if(event.jaxis.value < -m_joystickDeadZone){

            m_joystickValues[whichOne].first->setY(-1);

        } else {

            m_joystickValues[whichOne].first->setY(0);

        }
    }

    // right stick move left or right
    if(event.jaxis.axis == 3){
        if (event.jaxis.value > m_joystickDeadZone){

            m_joystickValues[whichOne].second->setX(1);

        } else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].second->setX(-1);
        } else {
            m_joystickValues[whichOne].second->setX(0);
        }
    }

    // right stick move up or down
    if(event.jaxis.axis == 4){
        if (event.jaxis.value > m_joystickDeadZone){
            m_joystickValues[whichOne].second->setY(1);
        } else if(event.jaxis.value < -m_joystickDeadZone){
            m_joystickValues[whichOne].second->setY(-1);
        } else {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
}


void ManagerInput::onJoystickButtonDown(SDL_Event &event){
    int whichOne = event.jaxis.which;

    m_buttonStates[whichOne][event.jbutton.button] = true;
}


void ManagerInput::onJoystickButtonUp(SDL_Event &event){
    int whichOne = event.jaxis.which;

    m_buttonStates[whichOne][event.jbutton.button] = false;
}


}