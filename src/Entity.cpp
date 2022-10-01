#include <iostream>
#include <Entity.h>



extern "C" {



Entity::Entity(ManagerEntity& manager): m_manager(manager) {
    this->m_bIsActive = true;
}


Entity::Entity( ManagerEntity& manager, std::string name ): m_manager(manager), m_name(name) {
    this->m_bIsActive = true;
}


void Entity::Update() {
    for (auto& component: m_components) {
		component->Update();
    }
}

void Entity::Render() {
    for (auto& component: m_components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->m_bIsActive = false;

	std::cout << "Entity::Destroy() -- 1 Entity DELETED" << std::endl;

	
}

bool Entity::IsActive() const {
    return this->m_bIsActive;
}


void Entity::ListAllComponents() const {
    for (auto mapElement: m_componentTypeMap) {
        std::cout << "    Component<" << mapElement.first->name() << ">" << std::endl;
    }
}


}