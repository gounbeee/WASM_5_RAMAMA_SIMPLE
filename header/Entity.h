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


    //  
    // https://en.cppreference.com/w/cpp/utility/forward


    // ----------------
    // < this POINTER >
    // https://monozukuri-c.com/langcpp-this-pointer/#toc2
    // :: this IS POINTINT TO 'INSTANCE OF THE CLASS OBJECT'
    //    SO WE CAN ACCESS THE MEMBER VARIABLES USING LIKE 
    //    this->m_foo, this->m_bar
    //
    //    1. MAKING INSTANCE
    //    CLASSNAME nnn( 10, 20 );
    //    
    //    2. LET'S ASSUME 
    //    CLASSNAME CLASS CONTAINTS aaa() METHOD
    //    
    //    3. CALLING METHOD
    //    nnn.aaa.()
    //
    //    4. HERE ACTUALLY &nnn IS TRANSFERED LIKE BELOW
    //    nnn.aaa.( &nnn )
    //              ~~~~
    //

    // ------------------------------------------------------------------------
    // < FUNCTION TEMPLATE AND PARAMETER PACK >
    // https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
    //
    // In a primary class template, the template parameter pack MUST BE THE 
    //                                                          ~~~~~~~~~~~
    // "FINAL PARAMETER" in the template parameter list. In a function template, 
    //  ~~~~~~~~~~~~~~~
    // the template parameter pack may appear earlier in the list provided 
    // that all following parameters can be deduced from the function arguments, 
    // or have default arguments:
    //
    //
    //      template <class... Args>
    //      struct X {
    //
    //        // EXPANDING PARAMETER PACK WITH "..." THEN,
    //        // PUT IN TO PARAMETER FOR CLASS-TEMPLATE WHICH IS std::tuple
    //
    //        std::tuple<Args...> values;
    //      };
    //    
    //      void g(int, char, const std::string&) {}
    //    
    //      template <class... Args>
    //      void f(Args... args)
    //      {
    //
    //        // EXPANDING PARAMETER PACK WITH "..." THEN,
    //        // PASS TO FUNCTION'S PARAMETER
    //        g(args...);
    //
    //      }
    //
    //      f(3, 'a', "hello");
    //
    //
    //       -------------------------------
    //       | TEMPLATE PARAMETERS         |
    //       | SO WE WILL USE THESE IN OUR |
    //       | TEMPLATE DEFINITION !!!!    | /->  typename... TArgs ->> SO, 
    //       |                             |      < MULTIPLE TYPES > WILL BE USED !!
	template <typename T, typename... TArgs> 
    T& AddComponent(TArgs&&... args) {       
    // T& IS RETURN TYPE
    // REFERENCE TYPE OF T CLASS < THIS IS "LVALUE" REFERENCE !!!! >
        //          ~~~~~~~~~~~~~~~
        //          TArgs&&... args
        //          |              \----->> args  IS NAME OF PARAMETER SO, THIS WILL BE TREATED 
        //          |                       AS A < LVALUE > FOR COMPILER !!
        //          v                            ----/
        //          TArgs IS CLASS NAME !!      /
        //                                     v
        //          < RVALUE REFERENCE??? NO !!! >  =  WE WILL EDIT INPUTTED VALUE ! WITHOUT "COPYING" !
        //                                             SO RVALUES' LIFETILE WILL BE EXPANDED THROUGH THIS FUNCTION
        //                                                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //                     + 
        //          < ... MEANS THAT NUMBER OF PARAMETERS WILL BE USED !! >
        //          


        // < std::forward<TArgs> >
        // :: CASTING PARAMETERS TO L | R VALUE DEPENDING ON CLASS 'T'
        //    HERE IN TEMPLATE FUNCTION, std::forward TRANSFER THE PARAMETER ABOVE
        //    SO THIS IS A "SWITCH" !!!!
        //    
        //
        // < PERFECT FORWARDING >
        // https://stackoverflow.com/questions/9671749/whats-the-difference-between-stdmove-and-stdforward
        //
        // :: std::forward HAS A SINGLE USE CASE: to cast a templated 
        //    function parameter (inside the function) 
        //    to the value category (lvalue or rvalue) the caller used 
        //    to pass it.
        //    This allows rvalue arguments to be passed on as rvalues, 
        //    and lvalues to be passed on as lvalues, a scheme called "perfect forwarding."
        //
        T* newComponent(new T(std::forward<TArgs>(args)...));       // Forward as lvalue or as rvalue, depending on T
        
        newComponent->owner = this;
        m_components.__emplace_back(newComponent);

        // STORING POINTER TO COMPONENT WITH MAP STRUCTURE
        // KEY VALUE IS "TYPEID"
		m_componentTypeMap[&typeid(*newComponent)] = newComponent;

        // RUN INITIALIZATION
        newComponent->Initialize();

        // RETURN "VALUE" OF NEW COMPONENT
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
