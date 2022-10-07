
#include <GameStatePlay.h>



const std::string GameStatePlay::s_playID = "PLAY";




extern "C" {







// CONSTRUCTOR
GameStatePlay::GameStatePlay( MultiVectorStr4& xmlData ):m_tileNumColumns(0), m_tileNumRows(0) {
	std::cout << "GameStatePlay::GameStatePlay() -- CONSTRUCTOR CALLED" << std::endl;
	m_xmlData = xmlData;
	GetTextureInfo( m_xmlData );
	GetObjectInfo( m_xmlData );
}


// DESTRUCTOR
GameStatePlay::~GameStatePlay() {
	std::cout << "GameStatePlay::~GameStatePlay() -- DESTRUCTOR CALLED" << std::endl;
}



bool GameStatePlay::OnEnter() {                                                     // WHEN WE ENTER PLAY STATE
	

	// PREPARING LEVEL
    LevelDataLoader levelDataLoader;
    m_pLevel = levelDataLoader.ParseTLSetterJson("resources/map01_json.json");			// PATH IS IMPORTANT !    TODO :: COLLECT TO ONE PLACE ?

	m_tileNumColumns = levelDataLoader.GetTileNumColumns();
	m_tileNumRows = levelDataLoader.GetTileNumRows();
	m_tileSize = levelDataLoader.GetTileSize();
    



	// std::cout << "m_pLevel is ...      " << m_pLevel << std::endl;
	// std::cout << "layerPnt is ...      " << layerPnt << std::endl;








	// PREPARING TEXTURES
	//Instance_ManagerTexture::Instance()->Load( "resources/texture_char_01.png", "char_01" , Instance_GameSDL::Instance()->GetRenderer() );
	//Instance_ManagerTexture::Instance()->Load( "resources/texture_btn_05_mainmenu.png", "btn_mainmenu" , Instance_GameSDL::Instance()->GetRenderer() );
	for( int i = 0 ; i < m_textureInfo.size() ; i++ ) {
		Instance_ManagerTexture::Instance()->Load( m_textureInfo[i][FILENAME] ,  m_textureInfo[i][ID] , Instance_GameSDL::Instance()->GetRenderer() );	
	}

	// PREPARING ENTITIES
	std::string id_player = m_objectInfo[0][TEXTUREID];
	Entity& player( Instance_ManagerEntity::Instance()->AddEntity( id_player.data() ));
	player.AddComponent<ComponentTransform>( std::stoi( m_objectInfo[0][XPOS] ) , std::stoi( m_objectInfo[0][YPOS] ) , std::stoi( m_objectInfo[0][VELOX] ), std::stoi( m_objectInfo[0][VELOY] ), std::stoi( m_objectInfo[0][WIDTH] ), std::stoi( m_objectInfo[0][HEIGHT] ), std::stoi( m_objectInfo[0][SCALE] ) );
	player.AddComponent<ComponentInputKeyboard>( SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_SPACE );
	player.AddComponent<ComponentPlayer>( 
		id_player.data() , 
		std::stoi( m_objectInfo[0][ANIMFRAMES]), 
		std::stoi( m_objectInfo[0][ANIMSPEED] ),
		std::stoi( m_objectInfo[0][STARTCOL] ),
		std::stoi( m_objectInfo[0][STARTROW] ) );

	std::string id_btn_mainmenu = m_objectInfo[1][TEXTUREID];
	Entity& btn_mainmenu( Instance_ManagerEntity::Instance()->AddEntity( id_btn_mainmenu.data() ));
	btn_mainmenu.AddComponent<ComponentTransform>( std::stoi( m_objectInfo[1][XPOS] ) , std::stoi( m_objectInfo[1][YPOS] ) , std::stoi( m_objectInfo[1][VELOX] ), std::stoi( m_objectInfo[1][VELOY] ), std::stoi( m_objectInfo[1][WIDTH] ), std::stoi( m_objectInfo[1][HEIGHT] ), std::stoi( m_objectInfo[1][SCALE] ) );
	btn_mainmenu.AddUIComponent<ComponentUIButton>( GameStatePlay::s_exitToMenu , id_btn_mainmenu.data() );

	std::string char_02_Id = m_objectInfo[2][TEXTUREID];
	Entity& char_02( Instance_ManagerEntity::Instance()->AddEntity( char_02_Id.data() ));
	char_02.AddComponent<ComponentTransform>( std::stoi( m_objectInfo[2][XPOS] ) , std::stoi( m_objectInfo[2][YPOS] ) , std::stoi( m_objectInfo[2][VELOX] ), std::stoi( m_objectInfo[2][VELOY] ), std::stoi( m_objectInfo[2][WIDTH] ), std::stoi( m_objectInfo[2][HEIGHT] ), std::stoi( m_objectInfo[2][SCALE] ) );
	//char_02.AddComponent<ComponentInputKeyboard>( SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_SPACE );
	char_02.AddComponent<ComponentPlayer>( 
		char_02_Id.data() , 
		std::stoi( m_objectInfo[2][ANIMFRAMES]), 
		std::stoi( m_objectInfo[2][ANIMSPEED] ),
		std::stoi( m_objectInfo[2][STARTCOL] ),
		std::stoi( m_objectInfo[2][STARTROW] ) );


    std::cout << "GameStatePlay::OnEnter() -- ENTERING PLAY GAMESTATE" << std::endl;

    return true;
}



void GameStatePlay::GetTextureInfo( MultiVectorStr4& xmlData ) {
	for( int i = 0; i < xmlData[PLAY][TEXTURES].size() ; i++ ) {		// xmlData[0][0] IS THE LAYER OF TEXTURES
		m_textureInfo.push_back( xmlData[PLAY][TEXTURES][i] );
	}
}


void GameStatePlay::GetObjectInfo( MultiVectorStr4& xmlData ) {
	for( int i = 0; i < xmlData[PLAY][OBJECTS].size() ; i++ ) {		// xmlData[0][1] IS THE LAYER OF OBJECTS
		m_objectInfo.push_back( xmlData[PLAY][OBJECTS][i] );
	}
}


void GameStatePlay::Update() {


	// RENDERING LEVEL WITH CAMERA
	if( m_pLevel != 0 ) {
		m_pLevel->Update();
	}


	// BG ANIMTION
 	// std::vector<Layer*>* layerPnt = m_pLevel->GetLayers();
 	// std::vector<Layer*> lyList = *layerPnt;

	// lyList[0]->SetVelocity( Vector2D{ -0.5f, 0.0f } );
	// lyList[1]->SetVelocity( Vector2D{ -0.7f, 0.0f } );




	// UPDATE ENTITIES
	Instance_ManagerEntity::Instance()->Update();

	// UPDATE GAME CAMERA
	// FIRST, GETTING PLAYER'S POSITION ( LOADING TRANSFORM COMPONENT )
	Entity* player = Instance_ManagerEntity::Instance()->GetEntityByName( "char_01" );
	ComponentTransform* playerTransformComponent = player->GetComponent<ComponentTransform>();
	Vector2D playerPosition = playerTransformComponent->GetPosition();

	// UPDATING CAMERA'S POSITION
	// CONSTRAINT TO PLAYER AND PLACE TO CENTER OF THE CAMERA
	int camPosX = (playerPosition.getX() + playerTransformComponent->GetWidth()/2) - Instance_GameSDL::Instance()->GetScreenWidth() / 2;
	int camPosY = (playerPosition.getY() + playerTransformComponent->GetHeight()/2) - Instance_GameSDL::Instance()->GetScreenHeight() / 2;
	
	// PROCESSES WHEN CAMERA RECT COLLIDES THE BOUNDARY OF THE MAP
	int boundaryX = m_tileNumColumns*m_tileSize - Instance_GameSDL::Instance()->GetScreenWidth();
	int boundaryY = m_tileNumRows*m_tileSize - Instance_GameSDL::Instance()->GetScreenHeight();
	if ( camPosX > 0 && camPosX < boundaryX ) { 
		Instance_GameSDL::Instance()->GetCamera()->x = camPosX;
	} else {
		Instance_GameSDL::Instance()->GetCamera()->x = Instance_GameSDL::Instance()->GetCamera()->x;
	}

	if ( camPosY > 0 && camPosY < boundaryY ) { 
		Instance_GameSDL::Instance()->GetCamera()->y = camPosY;
	} else {
		Instance_GameSDL::Instance()->GetCamera()->y = Instance_GameSDL::Instance()->GetCamera()->y;
	}
	
	// std::cout << "---------- playerPosition Pos X ::::   " << playerPosition.getX() << std::endl;
	// std::cout << "---------- playerPosition Pos Y ::::   " << playerPosition.getY() << std::endl;
	
	// std::cout << "@@@ Camera Pos X ::::   " << Instance_GameSDL::Instance()->GetCamera()->x << std::endl;
	// std::cout << "@@@ Camera Pos Y ::::   " << Instance_GameSDL::Instance()->GetCamera()->y << std::endl;


	/*
	// ADDITIONAL LEVEL'S MOVEMENT COULD BE MADE
	if( m_pLevel != 0 ) {
		Layer* layer = m_pLevel->GetLayerByIndex(1);						// IN THIS FUNCTION '1' IS THE FIRST LAYER ( NOT 0 )
		layer->SetVelocity( Vector2D( 1,0 ) );
		m_pLevel->Update();
	}
	*/







	// Entity* char_02 = Instance_ManagerEntity::Instance()->GetEntityByName( "char_02" );
	// ComponentTransform* char_02TransformComponent = char_02->GetComponent<ComponentTransform>();







	//std::cout << Instance_ManagerEntity::Instance()->GetEntityCount() << std::endl;
	//std::cout << "GameStatePlay::Update() -- UPDATING IN PLAY GAMESTATE" << std::endl;

}


void GameStatePlay::Render() {

	// RENDERING LEVEL WITH CAMERA
	if( m_pLevel != 0 ) {
		m_pLevel->Render();
	}







	/*
		// TEST FOR CAMERA
	SDL_Rect testRect = { 
		(int) Instance_GameSDL::Instance()->GetCamera()->x,
		(int) Instance_GameSDL::Instance()->GetCamera()->y,
		Instance_GameSDL::Instance()->GetCamera()->w ,
		Instance_GameSDL::Instance()->GetCamera()->h
	};
	
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 255, 55, 55, 50 );
	SDL_RenderFillRect( Instance_GameSDL::Instance()->GetRenderer() , &testRect );
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 0, 0, 0, 50);
	*/



	// RENDERING ENTITIES WITH CAMERA
	if( Instance_ManagerEntity::Instance()->HasNoEntities() ) {
		return;
	}


	Instance_ManagerEntity::Instance()->Render();







	//std::cout << "GameStatePlay::Render() -- RENDERING PLAY GAMESTATE......" << std::endl;
	
}



bool GameStatePlay::OnExit() {

	Instance_ManagerEntity::Instance()->Clean();

    std::cout << "exiting PlayState\n";
    return true;
}


// PRIVATE FUNCTIONS
void GameStatePlay::s_goToPause() {

    Instance_GameSDL::Instance()->GetGameStateMachine()->ChangeState( new GameStatePause( GameSDL::s_xmlData ) );

    std::cout << "Resume Button Clicked\n";
}

void GameStatePlay::s_exitToMenu(){

    Instance_GameSDL::Instance()->GetGameStateMachine()->ChangeState( new GameStateMenu( GameSDL::s_xmlData ) );
    std::cout << "Exit To Menu Button Clicked\n";

}




}
