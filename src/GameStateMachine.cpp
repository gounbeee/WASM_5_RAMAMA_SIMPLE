
#include <GameStateMachine.h>
#include <iostream>




extern "C" {


// CONSTRUCTOR
GameStateMachine::GameStateMachine(): m_gameStates(0) {
	std::cout << "GameStateMachine::GameStateMachine() -- CONSTRUCTOR CALLED" << std::endl;
}



// DESTRUCTOR
GameStateMachine::~GameStateMachine() {
	std::cout << "GameStateMachine::~GameStateMachine() -- DESTRUCTOR CALLED" << std::endl;

}


void GameStateMachine::Quit(){

    if(!m_gameStates.empty()){
        m_gameStates.back()->OnExit();

        delete m_gameStates.back();

        m_gameStates.clear();
    }

}


void GameStateMachine::Update(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->Update();
	}
}


void GameStateMachine::Render(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->Render();
    }
}


void GameStateMachine::PushState(GameState *pState){                            // ADDING STATE TO CURRENT STATE-STACK
    m_gameStates.push_back(pState);
    m_gameStates.back()->OnEnter();
}


void GameStateMachine::PopState(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->OnExit();
        m_gameStates.pop_back();
    }

    m_gameStates.back()->Resume();
}


void GameStateMachine::ChangeState(GameState *pState){
	
	// NOT EMPTY
    if(!m_gameStates.empty()){                                                  // IF THERE IS THE STATE ALREADY EXISTS

        if(m_gameStates.back()->GetStateID() == pState->GetStateID()){          // IF STATE NAME IS SAME AS THE ONE ALREADY EXISTS,
                                                                                // *pState == 'STATE ALREADY EXISTS'
                                                                                // DO NOTHING AND JUMP TO CALLER OF changeState()
            return; // do nothing
        }

		m_gameStates.back()->OnExit();                                          // SO, IF THERE IS THE STATE ALREADY EXISTS,
                                                                                // THEN IS DIFFERENT WITH INPUTTED ONE,
        // POPPING								(1)                             // WE WILL "EXIT" FROM PREVOIUS ONE, ( onExit() )
		m_gameStates.pop_back();                                                // THEN, POP THAT FROM VECTOR STORING STATES.
    }

	// initialise it
    pState->OnEnter();

	// PUSHING									(2)								(1)(2):: POP AND PUSH -> STACK STRUCTURE
    // push back our new state
    m_gameStates.push_back(pState);
}


}
