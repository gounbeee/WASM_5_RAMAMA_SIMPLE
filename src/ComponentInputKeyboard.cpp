
#include <ComponentInputKeyboard.h>



extern "C" {






// CONSTRUCTOR
ComponentInputKeyboard::ComponentInputKeyboard() {
	std::cout << "ComponentInputKeyboard::ComponentInputKeyboard() -- CONSTRUCTOR CALLED" << std::endl;
}

// CONSTRUCTOR WITH PARAMETER
ComponentInputKeyboard::ComponentInputKeyboard( SDL_Scancode upKey, 
												SDL_Scancode rightKey, 
												SDL_Scancode downKey, 
												SDL_Scancode leftKey, 
												SDL_Scancode writeKey) {
	m_Key_up = upKey;
	m_Key_right = rightKey;
	m_Key_down = downKey;
	m_Key_left = leftKey;
	m_Key_write = writeKey;

}


void ComponentInputKeyboard::Initialize() {
	std::cout << "ComponentInputKeyboard::Initialize() -- Initialize() CALLED" << std::endl;
	
	Key_Up = false;
	Key_Down = false;
	Key_Right = false;
	Key_Left = false;
	Key_Write = false;
}

void ComponentInputKeyboard::Update() {
    
	// IF KeyCode FROM EVENT LOOP IS MATCHED WITH ABOVE SETTINGS, DO SOMETHING
	
	// WHEN PRESSED
	if ( Instance_ManagerInput::Instance()->IsKeyDown( m_Key_up ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <UP> PRESSED" << std::endl;
		Key_Up = true;
		
	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyDown( m_Key_down ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <DOWN> PRESSED" << std::endl;
		Key_Down = true;
	
	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyDown( m_Key_left ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <LEFT> PRESSED" << std::endl;
		Key_Left = true;

	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyDown( m_Key_right ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <RIGHT> PRESSED" << std::endl;
		Key_Right = true;

	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyDown( m_Key_write ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <WRITE> PRESSED" << std::endl;
		Key_Write = true;
	}
	

	// WHEN UP
	if ( Instance_ManagerInput::Instance()->IsKeyUp( m_Key_up ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <UP> RELEASED" << std::endl;
		Key_Up = false;
		
	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyUp( m_Key_down ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <DOWN> RELEASED" << std::endl;
		Key_Down = false;
	
	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyUp( m_Key_left ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <LEFT> RELEASED" << std::endl;
		Key_Left = false;

	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyUp( m_Key_right ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <RIGHT> RELEASED" << std::endl;
		Key_Right = false;

	} 
	
	if ( Instance_ManagerInput::Instance()->IsKeyUp( m_Key_write ) ) {
		//std::cout << "ComponentInputKeyboard::Update() -- <WRITE> RELEASED" << std::endl;
		Key_Write = false;
	}
}




}