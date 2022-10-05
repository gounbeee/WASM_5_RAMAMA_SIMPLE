#ifndef INCLUDE_GUARD_COMPONENTPLAYER_H
#define INCLUDE_GUARD_COMPONENTPLAYER_H


#include <iostream>

#include "Component.h"
#include "ComponentTransform.h"
#include "Vector2D.h"
#include "ManagerTexture.h"


class ComponentTransform;
class ComponentInputKeyboard;
class ManagerTexture;

class ComponentPlayer : public Component {

public:
	ComponentPlayer( std::string textureID, int animFrames, float animSpeed, int startCol, int startRow );
	~ComponentPlayer();

	void Initialize();


	void Update();
	void Render();

	// GETTER AND SETTER FOR ANIMATION SPEED
	float GetAnimSpeed() const { return m_animSpeed; }
	void SetAnimSpeed( float newSpeed ) { 
		m_animSpeed = newSpeed; 
	}

	// GETTER AND SETTER FOR NUMBER OF ANIMATION FRAMES
	int GetAnimFrames() const { return m_animFrames; }
	void SetAnimFrames( int newNum ) { 
		m_animFrames = newNum; 
	}


private:
	ComponentTransform* m_transComponent;
	ComponentInputKeyboard* m_keybrdComponent;
	ManagerTexture* m_textureManager;
	
	std::string m_texID;
	
	int m_currentFrame;
	int m_animFrames;
	float m_animSpeed;

	unsigned int m_lastTime, m_newTime;

	int m_startCol;
	int m_startRow;

};

#endif