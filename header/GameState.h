
#ifndef INCLUDE_GUARD_GAMESTATE_H
#define INCLUDE_GUARD_GAMESTATE_H


#include <string>
#include <vector>
#include "GlobalTypes.h"
#include "ManagerLayers.h"


// THIS CLASS IS AN ABSTRACT CLASSES
// https://www.tutorialspoint.com/pure-virtual-functions-and-abstract-classes-in-cplusplus#:~:text=A%20pure%20virtual%20function%20is,least%20one%20pure%20virtual%20function.
// An abstract class is a class in C++ which have at least one pure virtual function.
// If an Abstract Class has derived class, they must implement all pure virtual functions, or else they will become Abstract too.
class GameState {
public:

    virtual ~GameState() {}                                                     // DESTRUCTOR

    virtual void Update() = 0;                                                  // THIS IS A PURE VIRTUAL FUNCTION
    virtual void Render() = 0;

    virtual bool OnEnter() = 0;
    virtual bool OnExit() = 0;

    virtual void Resume() {}


	// virtual void GetTextureInfo( MultiVectorStr4& xmlData ) = 0;
	// virtual void GetObjectInfo( MultiVectorStr4& xmlData ) = 0;

    virtual std::string GetStateID() const = 0;


protected:

	GameState() : m_loadingComplete(false), m_exiting(false){

    }

    GameState( MultiVectorStr4& xmlData ) : m_loadingComplete(false), m_exiting(false){

    }

    bool m_loadingComplete;
    bool m_exiting;

    std::vector<std::string> m_textureIDList;
	MultiVectorStr4 m_xmlData;

	MultiVectorStr2 m_textureInfo;
	MultiVectorStr2 m_objectInfo;

    ManagerLayers* m_managerLayers;
    

};



#endif
