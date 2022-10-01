#include <GameSDL.h>

// STATIC VARIABLES
GameSDL* GameSDL::s_pInstance = 0;
SDL_Rect* GameSDL::s_pCamera = 0;
MultiVectorStr4 GameSDL::s_xmlData = { { { {} } } } ;



extern "C" {



// CONSTRUCTOR
GameSDL::GameSDL() :	m_pSDLWindow(0), 
						m_pSDLRenderer(0), 
						m_bInitialized(false), 
						m_bLoopIsRunning(false), 
						m_pStateMachine(0), 
						m_gameWidth(0), 
						m_gameHeight(0), 
						m_screenWidth(0), 
						m_screenHeight(0) {

	// INITIALIZING CAMERA (RAW INITIALIZATION)
	if( s_pCamera == 0 ) {
		s_pCamera = new SDL_Rect();
		*s_pCamera = { 0, 0, 0, 0};
	}

	std::cout << "GameSDL()::GameSDL() -- CONSTRUCTOR CALLED" << std::endl;



}


// DESTRUCTOR
GameSDL::~GameSDL() {
	std::cout << "GameSDL()::~GameSDL() -- DESTRUCTOR CALLED" << std::endl;
	m_pSDLWindow = nullptr;
	m_pSDLRenderer = nullptr;
}



void GameSDL::Initialize( const char* appName , unsigned int xPos , unsigned int yPos , int xGameWidth, int yGameHeight, int xScrWidth , int yScrHeight , int windowFlag   ) {
	

	// ******* SDL ENGINE INITIALIZING ******* //
	// STORING WIDTH AND HEIGHT OF GAME
	m_gameWidth = xGameWidth;
	m_gameHeight = yGameHeight;

	m_screenWidth = xScrWidth;
	m_screenHeight = yScrHeight;


	// INITIALIZING CAMERA (REAL INITIALIZATION)
	if( s_pCamera != 0 ) *s_pCamera = { 0, 0, xScrWidth, yScrHeight};




	//SETTING UP SDL LIBRARY

	// < & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC ) >
	// https://github.com/emscripten-core/emscripten/issues/3139
	// :: THIS WAS FOR EMCC BUILD !!!!
	// 

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		std::cout << "GameSDL()::Initialize() -- ERROR OCCURED DURING INITIALIZE SDL" << std::endl;
		return;
	}

	// WINDOW
	m_pSDLWindow = SDL_CreateWindow( appName , xPos , yPos , m_screenWidth , m_screenHeight , windowFlag );

	// WINDOW CHECK
	if( m_pSDLWindow == nullptr ) {
		SDL_Quit();
		std::cout << "GameSDL()::Initialize() -- ERROR OCCURED DURING WINDOW INITIALIZATION" << std::endl;
		return;
	}

	m_pSDLRenderer = SDL_CreateRenderer( m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	// RENDERER CHECK
	if( m_pSDLRenderer == nullptr ) {
		SDL_DestroyWindow( m_pSDLWindow );
		SDL_Quit();
		std::cout << "GameSDL()::Initialize() -- ERROR OCCURED WHEN RENDERER INITIALIZATION" << std::endl;
		return;
	}
	
	// // SDL_ttf CHECK
	// if (TTF_Init() != 0){
	// 	SDL_Quit();
	// 	std::cout << "GameSDL()::Initialize() -- ERROR OCCURED WHEN SDL_ttf INITIALIZATION" << std::endl;
	// 	return;
	// }
	// ************************************** //


	// // INITIALIZE MANAGER-XML
	// ManagerXML managerXML;															// TODO :: ***** MAKE THE ARCHIVE *****
	// 																				// https://people.eecs.ku.edu/~jrmiller/Courses/JavaToC++/StackAllocatedObjects.html
	// 																				// IN C++, THIS IS A LOCAL VARIABLE AND INITIALIZED 
	// 																				// WITH NONE-PARAMETER CONTRUCTOR ( ManagerXML::ManagerXML() ),
	// 																				// ALLOCATING AT A STACK MEMORY( NOT USING 'NEW' ),
	// 																				// THEN WILL BE RELEASED AT THE END OF THIS FUNCTION ( GameSDL::Initialize() ).
	// 																				// **** BECAUSE THESE ARE DELETING SOON,
	// 																				//      SO WE NEED TO SEND THE DATA TO THE PROPER LOCATION ****
	
	// GameSDL::s_xmlData = managerXML.GetXmlOutput();



	// INITIALIZE INPUT CONTROLLER
    Instance_ManagerInput::Instance()->InitializeControllers();


	// INITIALIZE STATE MACHINE
	m_pStateMachine = new GameStateMachine();
	//m_pStateMachine->ChangeState( new GameStateMenu( GameSDL::s_xmlData ) );
	m_pStateMachine->ChangeState( new GameStateMenu() );


	// // INITIALIZE MANAGER-ENTITY
	Instance_ManagerEntity::Instance()->Initialize();


	// GAME INITIALIZATION IS OK
	m_bInitialized = true;
	
	// GAME LOOP FLAG TURN ON
	m_bLoopIsRunning = true;
	
}



void GameSDL::HandlingEvents() {

	Instance_ManagerInput::Instance()->Update();									// UPDATE() IN THE INPUT CONTROLLER CAN BE 
		
}



void GameSDL::Update() {

	// UPDATING STATES OF STATEMACHINE
	// ** THIS DOES ONLY MANAGING STATES
	//    THE FUNCTIONALITIES WILL BE RANGED TO POP AND PUSH THE STATES
	m_pStateMachine->Update();

}




void GameSDL::Render() {
	
	// CLEAR THE WINDOW
    SDL_RenderClear( m_pSDLRenderer );

	// RENDER STATES OF STATEMACHINE
	m_pStateMachine->Render();


    // SHOW THE WINDOW
    SDL_RenderPresent( m_pSDLRenderer );

}


void GameSDL::SetLoop( bool flag ) {
	m_bLoopIsRunning = flag;
}



void GameSDL::Quit() {

	// CLEANING SDL RENDERERS
	SDL_DestroyRenderer( m_pSDLRenderer );
	SDL_DestroyWindow( m_pSDLWindow );
	
	// DELETING POINTERS
	Instance_ManagerInput::Instance()->Quit();


	// EXIT APPLICATION
	SDL_Quit();

	std::cout << "GameSDL::Quit() -- PROPERLY PROCESSED" << std::endl;
}



}