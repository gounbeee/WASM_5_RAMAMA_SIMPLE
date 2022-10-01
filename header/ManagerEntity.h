
#ifndef INCLUDE_GUARD_ENTITYCONTROLLER_H
#define INCLUDE_GUARD_ENTITYCONTROLLER_H


#include "Entity.h"
#include "Component.h"
#include <vector>

class ManagerEntity {

public:

	static ManagerEntity* Instance() {											// MAKING THIS CLASS AS "SINGLETON"
		if( s_pInstance == 0 ){                                                 // ONLY IF THERE IS ANY INSTANCE
			s_pInstance = new ManagerEntity();									// CREATE THE NEW INSTANCE
		}
		return s_pInstance;                                                     // IF NOT, RETURN THAT INSTANCE
	}


	void Initialize();
    void Update();
    void Render();
   	void Clean();															// CLEAN 

	Entity& AddEntity( std::string entityName );

	void DestroyInactiveEntities();

	// GETTER FUNCTIONS
	bool HasNoEntities() const;
    unsigned int GetEntityCount() const;
	std::vector<Entity*> GetEntities() const;
	Entity* GetEntityByName(std::string entityName) const;
	ManagerEntity& GetReference() { return *this;	}


private:
    
	ManagerEntity();
	~ManagerEntity();

	static ManagerEntity* s_pInstance;
	std::vector<Entity*> m_entities;


};


typedef ManagerEntity Instance_ManagerEntity;

#endif