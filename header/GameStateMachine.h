
#ifndef INCLUDE_GUARD_GAMESTATEMACHINE_H
#define INCLUDE_GUARD_GAMESTATEMACHINE_H

#include <stack>
#include <vector>
#include "GameState.h"
#include "GameStatePlay.h"

class GameStateMachine
{
public:

    GameStateMachine();
    ~GameStateMachine();

    void Update();
    void Render();
    void Quit();

    void PushState(GameState* pState);
    void ChangeState(GameState* pState);
    void PopState();
	
	std::vector<GameState*>& GetGameStates() { return m_gameStates; }


private:
    std::vector<GameState*> m_gameStates;


};


#endif
