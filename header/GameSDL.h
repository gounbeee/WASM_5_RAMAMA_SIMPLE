
#ifndef INCLUDE_GUARD_GAME_H
#define INCLUDE_GUARD_GAME_H

#include <iostream>



#include "GlobalSettings.h"
#include "GlobalTypes.h"
// #include "GlobalFunctions.h"
#include "GlobalMath.h"
#include "ManagerEntity.h"
#include "ManagerTexture.h"
#include "ManagerInput.h"
#include "ManagerXML.h"
#include "GameStateMenu.h"
#include "GameStatePause.h"
#include "GameStatePlay.h"






class GameStateMachine;

class GameSDL {

private:
		
	GameSDL();																// CONSTRUCTOR
	~GameSDL();																// DESTRUCTOR
	
	static GameSDL* s_pInstance;											// UNIQUE INSTANCE IN THE ENTIRE APPLICATION USING SINGLETON PATTERN	
	static SDL_Rect* s_pCamera;												// CAMERA

	int m_gameWidth;
	int m_gameHeight;

	int m_screenWidth;
	int m_screenHeight;

	bool m_bInitialized;
	bool m_bLoopIsRunning;

	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;

	GameStateMachine* m_pStateMachine;

	

public:


	static GameSDL* Instance() {                                           // MAKING THIS CLASS AS "SINGLETON"
        if( s_pInstance == 0 ){                                            // ONLY IF THERE IS ANY INSTANCE 
            s_pInstance = new GameSDL();                                   // CREATE THE NEW INSTANCE
																		   // AT THIS TIME WE ARE USING HEAP
        }
        return s_pInstance;                                                // IF NOT, RETURN THAT INSTANCE

		//static GameSDL self;
		//return self;
	}
	
	// FOR STORING XML DATA
	static MultiVectorStr4 s_xmlData;


	// INITIALIZE GAME (SDL PART) INVOLED WITH SDL LIBRARY
	void Initialize( const char* appName , unsigned int xPos , unsigned int yPos , int xGameWidth, int yGameHeight, int xScrWidth , int yScrHeight , int windowFlag  );


	// HANDLING EVENTS
	void HandlingEvents();


	// UPDATE STATES
	void Update();


	// GAME LOOP (SDL PART) INVOLED WITH SDL LIBRARY
	void Render();


	// GAME (SDL PART) QUIT
	void Quit();




	// GETTERS AND SETTERS
	SDL_Rect* GetCamera() const { return s_pCamera; }



	// GETTER LOOP LOOP
	bool GetLoop() const {
		return m_bLoopIsRunning;
	}

	// GETTER FOR INIT FLAG
	bool GetInitFlag() const {
		return m_bInitialized;
	}
	
	// GETTER FOR GAME WIDTH
	int GetGameWidth() const  { return m_gameWidth; }
	
	// GETTER FOR GAME HEIGHT
	int GetGameHeight() const  { return m_gameHeight; }

	// GETTER FOR WIDTH
	int GetScreenWidth() const  { return m_screenWidth; }
	
	// GETTER FOR HEIGHT
	int GetScreenHeight() const  { return m_screenHeight; }


	// GETTER FOR STATE MACHINE
	GameStateMachine* GetGameStateMachine() const {
		return m_pStateMachine;
	}

	// GETTER FOR SDL RENDERER
	SDL_Renderer* GetRenderer() const {
		return m_pSDLRenderer;
	}
	

	// SETTER FOR LOOP
	void SetLoop( bool flag );

};

typedef GameSDL Instance_GameSDL;


#endif
