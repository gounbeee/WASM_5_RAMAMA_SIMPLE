
#ifndef INCLUDE_GUARD_GAMESTATEMENU_H
#define INCLUDE_GUARD_GAMESTATEMENU_H

#include <iostream>
#include <vector>
#include <emscripten.h>

#include "GameState.h"
#include "GameStateMachine.h"
#include "GameSDL.h"
#include "ComponentUIButton.h"
#include "ComponentInputKeyboard.h"
#include "ManagerTexture.h"
#include "Level.h"




# define EM_JS_EXT(ret, name, params, paramsInJS, ...) \
  _EM_JS_CPP_BEGIN                             \
  extern ret name params EM_IMPORT(name);      \
  __attribute__((used, visibility("default"))) \
  const char* __em_js__##name() {              \
    return #paramsInJS "<::>" #__VA_ARGS__;    \
  }                                            \
  _EM_JS_CPP_END





class GameStateMenu : public GameState {

public:

	GameStateMenu( MultiVectorStr4& xmlData );
	//GameStateMenu();
	~GameStateMenu();

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_menuID; }

	virtual void GetTextureInfo( MultiVectorStr4& xmlData );
	virtual void GetObjectInfo( MultiVectorStr4& xmlData );



private:

	static const std::string s_menuID;
	
	// CALLBACK FUNCTION FOR MENU ITEMS
	static void s_menuToPlay();
	static void s_aboutBtn();

	// Level* m_pLevel;
	// int m_tileNumColumns;
	// int m_tileNumRows;
	// int m_tileSize;



	
};




#endif
