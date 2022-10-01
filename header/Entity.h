#ifndef INCLUDE_GUARD_ENTITY_H
#define INCLUDE_GUARD_ENTITY_H

#include <vector>
#include <string>
#include <map>
#include <typeinfo> 
#include "ManagerEntity.h"
#include "Component.h"



class ManagerEntity;
class Component;

class Entity {

private:
    ManagerEntity& m_manager;
	std::string m_name;

    bool m_bIsActive;

    std::vector<Component*> m_components;
	std::map<const std::type_info*, Component*> m_componentTypeMap;

public:



    Entity(ManagerEntity& manager);
    Entity(ManagerEntity& manager, std::string name );


	void Update();
    void Render();
    void Destroy();
    bool IsActive() const;
	void ListAllComponents() const;
	std::string GetName() const { return m_name; }


	template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        T* newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        m_components.__emplace_back(newComponent);
		m_componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    }
	
	
	template < typename T, typename Function >
    T& AddUIComponent(Function&& callback , std::string&& texID ) {
        T* newComponent( new T( callback , texID ) );
        newComponent->owner = this;
        m_components.__emplace_back(newComponent);
		m_componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Initialize();
        return *newComponent;
    }
	


	
    template <typename T>
    bool HasComponent() const {
        return m_componentTypeMap.count(&typeid(T));
    }
	
	
    template <typename T>
    T* GetComponent() {
        return static_cast<T*>( m_componentTypeMap[&typeid(T)] );
    }
	
};

#endif
