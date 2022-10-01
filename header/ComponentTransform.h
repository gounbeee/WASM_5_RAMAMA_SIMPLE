#ifndef INCLUDE_GUARD_COMPONENTTRANSFORM_H
#define INCLUDE_GUARD_COMPONENTTRANSFORM_H


#include "GameSDL.h"
#include "ManagerEntity.h"
#include "Component.h"
#include "Vector2D.h"


class ComponentTransform : public Component {

private:
	Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    int m_scale;


public:

	ComponentTransform(int posX, int posY, int velX, int velY, int w, int h, int s);

    void Initialize();


	void Update();
	void Render();

	// GETTERS
	Vector2D GetPosition() const { return m_position; }
	Vector2D GetVelocity() const { return m_velocity; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	int GetScale() const { return m_scale; }

	// SETTERS
	void SetPosition( Vector2D& pos ) { m_position = pos; }
	void SetVelocity( Vector2D& vel ) { m_velocity = vel; }
	void SetWidth( int& val ) { m_width = val; }
	void SetHeight( int& val ) { m_height = val; }
	void SetScale( int& val ) { m_scale = val; }
};

#endif