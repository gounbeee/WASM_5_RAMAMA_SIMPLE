
#ifndef INCLUDE_GUARD_COMPONENTTIMELINE_H
#define INCLUDE_GUARD_COMPONENTTIMELINE_H


#include <iostream>

#include "Component.h"
#include "ComponentPlayer.h"
#include "ManagerXML.h"




class ComponentTimeline : public Component {


// WE NEED TO ANIMATE
// POSX POSY SCALEX, Y 


public:

	ComponentTimeline(const char* xmlFName);

	~ComponentTimeline();




    void Initialize();


	void Update();
	void Render();



private:


	ComponentPlayer* m_playerComponent;


	MultiVectorStr4 m_xmlData;

};







#endif