
#ifndef INCLUDE_GUARD_GAMESTATEPAUSE_H
#define INCLUDE_GUARD_GAMESTATEPAUSE_H


#include <iostream>
#include <vector>

#include "GameState.h"
#include "GameStateMachine.h"
#include "ManagerInput.h"
#include "GameSDL.h"



class GameStatePause : public GameState {

public:


	GameStatePause( MultiVectorStr4& xmlData );
	~GameStatePause();

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual void GetTextureInfo( MultiVectorStr4& xmlData );
	virtual void GetObjectInfo( MultiVectorStr4& xmlData );
	
	virtual std::string GetStateID() const { return s_pauseID; }


private:

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	//std::vector<GameObject*> m_gameObjects;

};


#endif
