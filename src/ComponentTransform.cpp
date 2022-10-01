#include <ComponentTransform.h>



extern "C" {



ComponentTransform::ComponentTransform(int posX, int posY, int velX, int velY, int w, int h, int s) {
	std::cout << "ComponentTransform::ComponentTransform() -- CONSTRUCTOR CALLED" << std::endl;
    m_position = Vector2D(posX, posY);
    m_velocity = Vector2D(velX, velY);
    m_width = w;
    m_height = h;
    m_scale = s;
}



void ComponentTransform::Initialize() {

}


void ComponentTransform::Update() {

	m_position += m_velocity;
}


void ComponentTransform::Render() {
	/*
	SDL_Rect testRect = { 
		(int) m_position.getX(),
		(int) m_position.getY(),
		m_width,
		m_height
	};
	
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 255, 255, 255, 255 );
	SDL_RenderFillRect( Instance_GameSDL::Instance()->GetRenderer() , &testRect );
	SDL_SetRenderDrawColor( Instance_GameSDL::Instance()->GetRenderer(), 0, 0, 0, 255);
	*/
}



}