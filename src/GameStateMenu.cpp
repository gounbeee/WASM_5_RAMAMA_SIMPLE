
#include <GameStateMenu.h>

#include <GameStatePlay.h>



const std::string GameStateMenu::s_menuID = "MENU";



extern "C" {



// PREPARING LEVEL
Level* m_pLevel;



// TESTING JSON LIBRARY

// CONSTRUCTOR
GameStateMenu::GameStateMenu( MultiVectorStr4& xmlData ) {
	std::cout << "GameStateMenu::GameStateMenu() -- CONSTRUCTOR CALLED" << std::endl;
	

	m_xmlData = xmlData;

	GetTextureInfo( m_xmlData );
	GetObjectInfo( m_xmlData );


}


// DESTRUCTOR
GameStateMenu::~GameStateMenu() {
	std::cout << "GameStateMenu::~GameStateMenu() -- DESTRUCTOR CALLED" << std::endl;
}



// PUBLIC FUNCTIONS
bool GameStateMenu::OnEnter() {

	
	// TODO :: USE m_textureInfo AND m_objectInfo TO STRINGS 

	// PREPARING TEXTURES
	// Instance_ManagerTexture::Instance()->Load( "resources/texture_btn_01_play.png", "btn_play" , Instance_GameSDL::Instance()->GetRenderer() );
	// Instance_ManagerTexture::Instance()->Load( "resources/texture_btn_02_about.png", "btn_about" , Instance_GameSDL::Instance()->GetRenderer() );


	for( int i = 0 ; i < m_textureInfo.size() ; i++ ) {
		Instance_ManagerTexture::Instance()->Load( m_textureInfo[i][FILENAME] ,  m_textureInfo[i][ID] , Instance_GameSDL::Instance()->GetRenderer() );	
	}




	// PREPARING ENTITIES
	// **** DEPENDENCY BETWEEN COMPONENTS ****
	// :: THE ORDER IS CRITICAL !!!!
	// :: BELOW, "ComponentTransform" IS NEEDED FOR "Initialize()"-ING "ComponentUIButton"
	//    IF, ComponentUIButton( WHICH USES ComponentTransform ) ADDED EARLIER 
	//    AND TRANSFORM COMPONENT LATER, 
	//    IT WILL ACHIEVE "NULL" POINTER TO ComponentTransform TO m_transComponent VARIABLE,
	//    THEN WILL USE AT THE UPDATE FUNCTION, SO IT WILL CRASH !!!!

	// ******************************************
	// TODO :: HOW TO CONVERT STRINGS FROM VECTOR WITH NULL END


	std::string id_a = m_objectInfo[0][TEXTUREID];
	

	// CHANGING SIZE OF STRING
	// http://www.cplusplus.com/reference/string/string/resize/
	//unsigned int size_id_a = id_a.size();
	//id_a.resize( size_id_a+1, '\0');
	Entity& but_a( Instance_ManagerEntity::Instance()->AddEntity( id_a.data() ));
	but_a.AddComponent<ComponentTransform>( std::stoi( m_objectInfo[0][XPOS] ) , std::stoi( m_objectInfo[0][YPOS] ) , std::stoi( m_objectInfo[0][VELOX] ), std::stoi( m_objectInfo[0][VELOY] ), std::stoi( m_objectInfo[0][WIDTH] ), std::stoi( m_objectInfo[0][HEIGHT] ), std::stoi( m_objectInfo[0][SCALE] ) );
	but_a.AddUIComponent<ComponentUIButton>( GameStateMenu::s_menuToPlay , id_a.data() );
	


	std::string id_b = m_objectInfo[1][TEXTUREID];
	//unsigned int size_id_b = id_b.size();
	//id_b.resize( size_id_b+1, '\0');
	Entity& but_b( Instance_ManagerEntity::Instance()->AddEntity( id_b.data() ));
	but_b.AddComponent<ComponentTransform>( std::stoi( m_objectInfo[1][XPOS] ) , std::stoi( m_objectInfo[1][YPOS] ) , std::stoi( m_objectInfo[1][VELOX] ), std::stoi( m_objectInfo[1][VELOY] ), std::stoi( m_objectInfo[1][WIDTH] ), std::stoi( m_objectInfo[1][HEIGHT] ), std::stoi( m_objectInfo[1][SCALE] ) );
	but_b.AddUIComponent<ComponentUIButton>( GameStateMenu::s_aboutBtn , id_b.data() );





	
	// Entity& but_a( Instance_ManagerEntity::Instance()->AddEntity("btn_play"));
	// but_a.AddComponent<ComponentTransform>( 200, 100, 0, 0, 400, 100, 1 );
	// but_a.AddUIComponent<ComponentUIButton>( GameStateMenu::s_menuToPlay , "btn_play" );
	
	// Entity& but_b( Instance_ManagerEntity::Instance()->AddEntity("btn_about"));
	// but_b.AddComponent<ComponentTransform>( 200, 300, 0, 0, 400, 100, 1 );
	// but_b.AddUIComponent<ComponentUIButton>( GameStateMenu::s_exitFromMenu , "btn_about" );
	

    std::cout << "GameStateMenu::OnEnter() -- ENTERING MENU GAMESTATE" << std::endl;
    return true;
}


void GameStateMenu::GetTextureInfo( MultiVectorStr4& xmlData ) {

	for( int i = 0; i < xmlData[MENU][TEXTURES].size() ; i++ ) {		// xmlData[0][0] IS THE LAYER OF TEXTURES
		m_textureInfo.push_back( xmlData[MENU][TEXTURES][i] );
	}

}


void GameStateMenu::GetObjectInfo( MultiVectorStr4& xmlData ) {

	for( int i = 0; i < xmlData[MENU][OBJECTS].size() ; i++ ) {		// xmlData[0][1] IS THE LAYER OF OBJECTS
		m_objectInfo.push_back( xmlData[MENU][OBJECTS][i] );
	}

}



void GameStateMenu::Update() {

	Instance_ManagerEntity::Instance()->Update();

	//std::cout << "GameStateMenu::Update() -- UPDATING IN MENU GAMESTATE" << std::endl;

}

void GameStateMenu::Render() {

	Instance_ManagerEntity::Instance()->Render();

	//std::cout << "GameStateMenu::Render() -- RENDERING MENU GAMESTATE......" << std::endl;
	

	// RENDERING LEVEL WITH CAMERA
	if( m_pLevel != 0 ) {
		m_pLevel->Render();
	}



}

bool GameStateMenu::OnExit() {

	Instance_ManagerEntity::Instance()->Clean();

	Instance_ManagerTexture::Instance()->ClearFromTextureMap("btn_play");
	Instance_ManagerTexture::Instance()->ClearFromTextureMap("btn_about");

    std::cout << "exiting MenuState\n";
    return true;
}



// PRIVATE FUNCTIONS
void GameStateMenu::s_menuToPlay() {





	Instance_GameSDL::Instance()->GetGameStateMachine()->ChangeState( new GameStatePlay( GameSDL::s_xmlData ) );




   	std::cout << "Play Button Clicked\n";
}







void GameStateMenu::s_aboutBtn(){

    Instance_GameSDL::Instance()->SetLoop( false );


    std::cout << "ABOUT Button Clicked\n";




    LevelDataLoader levelDataLoader;
    m_pLevel = levelDataLoader.ParseTLSetterJson("resources/map01_json.json");			// PATH IS IMPORTANT !    TODO :: COLLECT TO ONE PLACE ?



}





}
