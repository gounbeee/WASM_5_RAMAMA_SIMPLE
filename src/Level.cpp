

#include <Level.h>



extern "C" {



Level::Level()
{
}

Level::~Level()
{
    std::cout << "~Level() CALLED" << std::endl;

    for(int i = 0; i < m_layers.size(); i++)
    {
        delete m_layers[i];
    }

    m_layers.clear();
}


void Level::Update() {

    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i]->Update();
    }

}


void Level::Render() {

    //std::cout << "  - IN Level.cpp:30 ===  m_layers.size() IS ----   " << m_layers.size() << std::endl;

    for(int i = 0; i < m_layers.size(); i++) {


        m_layers[i]->Render();

    }
}



Layer* Level::GetLayerByIndex( int index ) { 
	if( index > 0 ) {
		return *&m_layers[index-1]; 
	}
}






}