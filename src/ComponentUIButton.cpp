#include <ComponentUIButton.h>



extern "C" {



int g_scale = GLOBAL_SCALE_2;



ComponentUIButton::ComponentUIButton( void (*callback)() , std::string textureID ) : m_callback( callback ), m_texID( textureID ) {
    std::cout << "ComponentUIButton::ComponentUIButton() -- CONSTRUCTOR CALLED" << std::endl;
	m_currentFrame = MOUSE_OUT;                                                             // START AT FRAME 0 (THE PICTURE WHEN ANY MOUSE WAS OVER) 

}


void ComponentUIButton::Initialize() {
	std::cout << "ComponentUIButton::Initialize() -- Initialize() CALLED" << std::endl;

	// GETTING TRANSFORM COMPONENT
	m_transComponent = owner->GetComponent<ComponentTransform>();
	
	// GETTING TEXTURE MANAGER
	m_textureManager = Instance_ManagerTexture::Instance();
}


void ComponentUIButton::Update() {


    Vector2D* pMousePos = Instance_ManagerInput::Instance()->GetMousePosition();                  // GETTING MOUSE CURSOR POSITION

    int xMinCoord = m_transComponent->GetPosition().getX() * g_scale;
	int xMaxCoord = (m_transComponent->GetPosition().getX() + m_transComponent->GetWidth()) * g_scale;
    int yMinCoord = m_transComponent->GetPosition().getY() * g_scale;
	int yMaxCoord = (m_transComponent->GetPosition().getY() + m_transComponent->GetHeight()) * g_scale;
    
    // std::cout << "xMinCoord  ->   " << xMinCoord << std::endl;
    // std::cout << "xMaxCoord  ->   " << xMaxCoord << std::endl;
    // std::cout << "yMinCoord  ->   " << yMinCoord << std::endl;
    // std::cout << "yMaxCoord  ->   " << yMaxCoord << std::endl;


	// COLLISION TEST
	// TODO :: SEPERATE TO NEW COMPONENT FOR COLLISION CHECK
    if( pMousePos->getX() > xMinCoord && 
    	pMousePos->getX() < xMaxCoord &&
        pMousePos->getY() > yMinCoord &&
        pMousePos->getY() < yMaxCoord ) {                                        

        // AREA COLLISION TEST IF MOUSE CURSOR IS "OVER"
		//std::cout << "ComponentUIButton::Update() -- MOUSE IS OVER" << std::endl;
        
        m_currentFrame = MOUSE_OVER;

        if(Instance_ManagerInput::Instance()->GetMouseButtonState(LEFT) && m_bReleased ) {    // CHECKS LEFT MOUSE BUTTON WAS PRESSED THEN RELEASED
			//std::cout << "ComponentUIButton::Update() -- MOUSE BUTTON PRESSED!" << std::endl;
            
            m_currentFrame = CLICKED;                                                   // CLICKED!

            m_callback();                                                               // RUN CALLBACK FUNCTION

            m_bReleased = false;                                                        // NOW MOUSE BUTTON IS PRESSED

        } else if ( !Instance_ManagerInput::Instance()->GetMouseButtonState(LEFT) ) {
            m_bReleased = true;                                                         // MOUSE BUTTON IS RELEASED
            m_currentFrame = MOUSE_OVER;                                                // RETURN TO STATE TO "OVER"
        }

    } else {

        m_currentFrame = MOUSE_OUT;                                                     // NOW MOUSE IS NOT IN THE AREA

    }

	
}


void ComponentUIButton::Render() {

	//std::cout << "g_scale  ->   " << g_scale << std::endl;

	m_textureManager->RenderFrame(	m_texID, 
									m_transComponent->GetPosition().getX(), 
									m_transComponent->GetPosition().getY(), 
									m_transComponent->GetWidth(), 
									m_transComponent->GetHeight(), 
									0,
									0,
									m_currentFrame,
									g_scale,
									Instance_GameSDL::Instance()->GetRenderer() , 
									SDL_FLIP_NONE );

	
	/*
	// TESTING LIKE BELOW IS GOOD FOR STARTING POINT OF PROJECT
	// ******** TODO :: ARCHIVE BELOW ********
    SDL_Rect testRect = { 
		150,
		150,
		50,
		50
	};
	
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 255, 0, 255, 255 );
	SDL_RenderFillRect( Instance_GameSDL::Instance()->GetRenderer() , &testRect );
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 0, 0, 0, 255);                                                               // USING BASE CLASS'S FUNCTION
	*/
}



}


