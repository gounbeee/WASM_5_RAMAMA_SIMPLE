#include <iostream>
#include <ManagerEntity.h>



extern "C" {




ManagerEntity* ManagerEntity::s_pInstance = 0;

// CONSTRUCTOR
ManagerEntity::ManagerEntity() {
	std::cout << "ManagerEntity::ManagerEntity() -- CONSTRUCTOR CALLED" << std::endl;

}

// DESTRUCTOR
ManagerEntity::~ManagerEntity() {
	std::cout << "ManagerEntity::~ManagerEntity() -- DESTRUCTOR CALLED" << std::endl;

}



void ManagerEntity::Initialize() {
	std::cout << "ManagerEntity::Initialize() -- Initialize CALLED" << std::endl;

}


void ManagerEntity::Clean() {
	std::cout << "ManagerEntity::Clean() -- Cleaning Entities..." << std::endl;
    for (auto& entity: m_entities) {
        entity->Destroy();
    }
}

void ManagerEntity::Update() {
	DestroyInactiveEntities();

	// TODO:: CRASHED WHEN I USED RANGED BASED LOOP WITH CHAINGING STATE USING KEY INPUT
	// https://stackoverflow.com/questions/14429338/why-is-my-range-based-for-loop-crashing-my-c-program
    for ( int i = 0 ; i < m_entities.size() ; i++ ) {
		m_entities[i]->Update();
    }

}

void ManagerEntity::Render() {
    for (auto& entity: m_entities ) {
        entity->Render();
    }
}

void ManagerEntity::DestroyInactiveEntities() {
    for (int i = 0; i < m_entities.size(); i++) {
        if (!m_entities[i]->IsActive()) {
            m_entities.erase(m_entities.begin() + i);
        }
    }
}

bool ManagerEntity::HasNoEntities() const {
    return m_entities.size() == 0;
}


unsigned int ManagerEntity::GetEntityCount() const {
    return m_entities.size();
}


std::vector<Entity*> ManagerEntity::GetEntities() const {
    return m_entities;
}


Entity& ManagerEntity::AddEntity( std::string entityName ) {
    Entity* entity = new Entity( *this, entityName );
    m_entities.emplace_back(entity);
    return *entity;
}


Entity* ManagerEntity::GetEntityByName(std::string entityName) const {
    for (auto* entity: m_entities) {
        if (entity->GetName().compare(entityName) == 0) {
            return entity;
        }
    }
    return NULL;
}


}
