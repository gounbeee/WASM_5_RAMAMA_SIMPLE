
#ifndef INCLUDE_GUARD_GAMESTATEPLAY_H
#define INCLUDE_GUARD_GAMESTATEPLAY_H

#include <iostream>
#include "GameSDL.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "GameStatePause.h"
#include "Entity.h"
#include "ComponentTransform.h"
#include "ComponentPlayer.h"
#include "Level.h"

class Level;


class GameStatePlay : public GameState {

public:

	GameStatePlay( MultiVectorStr4& xmlData );
	~GameStatePlay();

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_playID; }

	virtual void GetTextureInfo( MultiVectorStr4& xmlData );
	virtual void GetObjectInfo( MultiVectorStr4& xmlData );


private:
	

	static const std::string s_playID;

	Level* m_pLevel;
	int m_tileNumColumns;
	int m_tileNumRows;
	int m_tileSize;

	// CALLBACK FUNCTIONS
	static void s_goToPause(); 
	static void s_exitToMenu();
};


#endif
