
#include <GameStatePause.h>


const std::string GameStatePause::s_pauseID = "PAUSE";




extern "C" {




// CONSTRUCTOR
GameStatePause::GameStatePause( MultiVectorStr4& xmlData ) {
	std::cout << "GameStatePause::GameStatePause() -- CONSTRUCTOR CALLED" << std::endl;
	m_xmlData = xmlData;
	GetTextureInfo( m_xmlData );
	GetObjectInfo( m_xmlData );
}


// DESTRUCTOR
GameStatePause::~GameStatePause() {
	std::cout << "GameStatePause::~GameStatePause() -- DESTRUCTOR CALLED" << std::endl;
}




bool GameStatePause::OnEnter() {

	/*
    if( !TheTextureManager::Instance()->load("resources/resume.png", "resumebutton", TheGame::Instance()->getRenderer()) ) {
        return false;
    }

    if( !TheTextureManager::Instance()->load("resources/main.png", "mainbutton", TheGame::Instance()->getRenderer()) ) {
        return false;
    }


    GameObject* button1 = new UIButton( s_pauseToMain );
    GameObject* button2 = new UIButton( s_resumePlay );

    button1->load( new LoaderParams( 200, 100, 200, 80, 1, 1, "mainbutton", 1, 0, 1 ) );
    button2->load( new LoaderParams( 200, 300, 200, 80, 1, 1, "resumebutton", 1, 0, 1 ) );

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
	*/


    std::cout << "GameStatePause::OnEnter() -- ENTERING PAUSE GAMESTATE" << std::endl;

    return true;
}



// PUBLIC FUNCTIONS
void GameStatePause::Update() {

	/*
    for(int i = 0; i < m_gameObjects.size(); i++) {

        m_gameObjects[i]->update();

    }
	*/

	//std::cout << "GameStatePause::Update() -- UPDATING IN PAUSE GAMESTATE" << std::endl;
}


void GameStatePause::Render() {

	/*
    for( int i = 0; i < m_gameObjects.size(); i++ ) {
        m_gameObjects[i]->draw();
    }
	*/

	//std::cout << "GameStatePause::Render() -- RENDERING PAUSE GAMESTATE......" << std::endl;
	
}




bool GameStatePause::OnExit() {
    
	/*
	for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	*/


    // reset the mouse button states to false
    //Instance_InputController::Instance()->Reset();


    std::cout << "exiting PauseState\n";

    return true;
}


void GameStatePause::GetTextureInfo( MultiVectorStr4& xmlData ) {
	for( int i = 0; i < xmlData[0][0].size() ; i++ ) {		// xmlData[0][0] IS THE LAYER OF TEXTURES
		m_textureInfo.push_back( xmlData[0][0][i] );
	}
}


void GameStatePause::GetObjectInfo( MultiVectorStr4& xmlData ) {
	for( int i = 0; i < xmlData[0][1].size() ; i++ ) {		// xmlData[0][1] IS THE LAYER OF OBJECTS
		m_objectInfo.push_back( xmlData[0][1][i] );
	}

}



// PRIVATE FUNCTIONS
void GameStatePause::s_pauseToMain() {

    //TheGame::Instance()->getGameStateMachine()->changeState( new GameStateMenu() );

}


void GameStatePause::s_resumePlay() {

    //TheGame::Instance()->getGameStateMachine()->popState();

}






}