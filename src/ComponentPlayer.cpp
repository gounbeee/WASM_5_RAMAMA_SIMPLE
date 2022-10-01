
#include <ComponentPlayer.h>




extern "C" {




ComponentPlayer::ComponentPlayer( std::string textureID, int animFrames, float animSpeed ):  
															m_transComponent(0), 
															m_keybrdComponent(0), 
															m_texID(textureID), 
															m_currentFrame(0), 
															m_animFrames(animFrames), 
															m_animSpeed(animSpeed),
															m_lastTime(0),
															m_newTime(0) {
	std::cout << "ComponentPlayer::ComponentPlayer() -- CONSTRUCTOR CALLED" << std::endl;
}


ComponentPlayer::~ComponentPlayer() {
	std::cout << "ComponentPlayer::~ComponentPlayer() -- DESTRUCTOR CALLED" << std::endl;
}



void ComponentPlayer::Initialize() {
	std::cout << "ComponentPlayer::Initialize() -- Initialize() CALLED" << std::endl;
	


	// GETTING TRANSFORM COMPONENT
	m_transComponent = owner->GetComponent<ComponentTransform>();

	// GETTING KEYBOARD INPUT COMPONENT
	m_keybrdComponent = owner->GetComponent<ComponentInputKeyboard>();

	// GETTING TEXTURE MANAGER
	m_textureManager = Instance_ManagerTexture::Instance();




	// RESET TIMERS FOR ANIMATING
	m_newTime = SDL_GetTicks();
	m_lastTime = SDL_GetTicks();
}


void ComponentPlayer::Update() {
	// ANIMATING TEXTURE
	m_newTime = SDL_GetTicks();
	unsigned int deltaTime = m_newTime - m_lastTime;
	
	m_currentFrame = (int) ( ( (float) deltaTime / 1000.0f ) * m_animSpeed ) % m_animFrames;


	// ANIMATING POSITION
	// RESET VELOCITY
	Vector2D addedVelocity{ 0.0f , 0.0f };
	




	// WHEN UP KEY PRESSED
	if( m_keybrdComponent->Key_Up ) { 
		//std::cout << "Key_Up" << std::endl;
		addedVelocity += Vector2D( 0.0f, -5.0f);
	}
	// WHEN DOWN KEY PRESSED
	if( m_keybrdComponent->Key_Down ) { 
		//std::cout << "Key_Down" << std::endl;
		addedVelocity += Vector2D( 0.0f, 5.0f );
	}
	// WHEN LEFT KEY PRESSED
	if( m_keybrdComponent->Key_Left ) { 
		//std::cout << "Key_Left" << std::endl;
		addedVelocity += Vector2D( -5.0f, 0.0f );
	}
	// WHEN LEFT KEY PRESSED
	if( m_keybrdComponent->Key_Right ) { 
		//std::cout << "Key_Right" << std::endl;
		addedVelocity += Vector2D( 5.0f, 0.0f );
	}
	m_transComponent->SetVelocity( addedVelocity );


	// WHEN WRITE KEY PRESSED
	if( m_keybrdComponent->Key_Write ) { 
		//std::cout << "Key_Write" << std::endl;
		std::cout << "ComponentPlayer::Update() -- WRITE SOMETHING !!" << std::endl;
	}




}




void ComponentPlayer::Render() {
	
	m_textureManager->RenderFrame(	m_texID, 
								m_transComponent->GetPosition().getX() - (int) Instance_GameSDL::Instance()->GetCamera()->x , 
								m_transComponent->GetPosition().getY() - (int) Instance_GameSDL::Instance()->GetCamera()->y, 
								m_transComponent->GetWidth(), 
								m_transComponent->GetHeight(), 
								1,
								7,
								m_currentFrame,
								Instance_GameSDL::Instance()->GetRenderer() , SDL_FLIP_NONE );

}




}



