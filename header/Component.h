#ifndef INCLUDE_GUARD_COMPONENT_H
#define INCLUDE_GUARD_COMPONENT_H

class Entity;


class Component
{
    public:
        Entity* owner;
        virtual ~Component() {}
        virtual void Initialize() {}
		virtual void Update() {}
        virtual void Render() {}


};


#endif