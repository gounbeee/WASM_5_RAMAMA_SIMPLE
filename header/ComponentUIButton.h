
#ifndef INCLUDE_GUARD_COMPONENTUIBUTTON_H
#define INCLUDE_GUARD_COMPONENTUIBUTTON_H


#include "ComponentTransform.h"
#include "ManagerEntity.h"
#include "Component.h"
#include "Vector2D.h"
#include "EntityDataLoader.h"
#include "ManagerTexture.h"


// BELOW FORWARD DECLARATION AND 
// 'NOT' TO ADD #include "ComponentTransform.h" IS CRITICAL
// NOT TO ENTER THE "CIRCULAR DEPENDENCY"
class ComponentTransform;

class ComponentUIButton : public Component {


private:
	
	// ENUM WILL BE USED FOR INDICATING ANIMATION FRAME
    enum button_state {                                                         // BUTTON STATE ENUM
        MOUSE_OUT = 0,                                                          // THIS WILL BE m_currentFrame VARIABLE
        MOUSE_OVER = 1,                                                         // FOR CHANGING FRAME NUMBER OF TEXTURE
        CLICKED = 2
    };

	std::string m_texID;
	int m_currentFrame;															// CURRENT FRMAE NUMBER OF ANIMATION
    bool m_bReleased;                                                           // FOR CHECKING MOUSE BUTTON RELEASED
	void (*m_callback)();
	ManagerTexture* m_textureManager;
	ComponentTransform* m_transComponent;

public:

    ComponentUIButton( void (*callback)() , std::string textureID);

	void Initialize();
	void Update();
    void Render();
    




};



#endif
