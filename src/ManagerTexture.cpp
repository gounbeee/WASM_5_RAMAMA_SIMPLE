
#include <ManagerTexture.h>
#include <GameSDL.h>



extern "C" {



ManagerTexture* ManagerTexture::s_pInstance = 0;



ManagerTexture::ManagerTexture() {
	std::cout << "ManagerTexture::ManagerTexture() -- CONSTRUCTOR CALLED" << std::endl;

}

ManagerTexture::~ManagerTexture() {
	std::cout << "ManagerTexture::ManagerTexture() -- DESTRUCTOR CALLED" << std::endl;

}



// LOADING IMAGE TO TEXTURE
bool ManagerTexture::Load( std::string fileName, std::string id, SDL_Renderer* pRenderer ){
    SDL_Surface* pTempSurface = IMG_Load( fileName.c_str() );                                       // TAKING FILE NAME OF IMAGE

    if( pTempSurface == 0 ) {                                                                       // IF THE RESULT OF IMG_Load() IS NULL
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface( pRenderer, pTempSurface );                // CREATING TEXTURE USING SDL LIBRARY
    SDL_FreeSurface( pTempSurface );                                                                // TODO :: WHY DO WE FREE THE SURFACE?

    if( pTexture != 0 ) {                                                                           // IF OK, ADD THE TEXTURE TO THE LIST
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;                                                                                   // IF THERE IS SOMETHING WRONG
}


// DRAWING TEXTURE WITH NO-ANIMATION
void ManagerTexture::Render( std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip ){
    SDL_Rect srcRect;                                                                           // SOURCE AREA ON THE TEXTURE
    SDL_Rect destRect;                                                                          // DESTNINATION ON THE SCREEN

    srcRect.x = 0;                                                                              // STARTING POINT X OF SOURCE TEXTURE
    srcRect.y = 0;                                                                              // STARTING POINT Y OF SOURCE TEXTURE
    srcRect.w = destRect.w = width;                                                             // WE DON'T WANT TO BE SCALED SO RECTANGLE AREA OF TEXTURE SHOULD BE SAME
    srcRect.h = destRect.h = height;                                                            // WE DON'T WANT TO BE SCALED SO RECTANGLE AREA OF TEXTURE SHOULD BE SAME
    destRect.x = x;                                                                             // DESTINATION AREA POSITION X OF THE SCREEN
    destRect.y = y;                                                                             // DESTINATION AREA POSITION Y OF THE SCREEN

    SDL_RenderCopyEx( pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip );

}



// DRAWING TEXTURE WITH ANIMATION
void ManagerTexture::RenderFrame(	std::string id, 
									int x, 
									int y, 
									int width, 
									int height, 
									int currentColumn, 
									int currentRow,  
									int currentFrame, 
                                    int scale,
									SDL_Renderer* pRenderer, 
									SDL_RendererFlip flip ){


    SDL_Rect srcRect;                                                                           // SOURCE AREA ON THE TEXTURE
    SDL_Rect destRect;                                                                          // DESTNINATION ON THE SCREEN

    srcRect.x = currentColumn * width + currentFrame * width;                             // STARTING POINT X OF SOURCE TEXTURE
                                                                                                // width * currentFrame IS THE "CURSOR" TO ANIMATE
    srcRect.y = currentRow * height;                                                       // STARTING POINT Y OF SOURCE TEXTURE

    srcRect.w = width;                                                             // WE DON'T WANT TO BE SCALED SO RECTANGLE AREA OF TEXTURE SHOULD BE SAME
    srcRect.h = height;                                                            // WE DON'T WANT TO BE SCALED SO RECTANGLE AREA OF TEXTURE SHOULD BE SAME

    destRect.w = width * scale;  
    destRect.h = height * scale; 

    destRect.x = x * scale;                                                                             // DESTINATION AREA POSITION X OF THE SCREEN
    destRect.y = y * scale;                                                                             // DESTINATION AREA POSITION Y OF THE SCREEN


    // std::cout << "scale  ->   " << scale << std::endl;
    // std::cout << "srcRect.x  ->   " << srcRect.x << std::endl;
    // std::cout << "srcRect.y  ->   " << srcRect.y << std::endl;
    // std::cout << "srcRect.w  ->   " << srcRect.w << std::endl;
    // std::cout << "srcRect.h  ->   " << srcRect.h << std::endl;
    // std::cout << "destRect.x  ->   " << destRect.x << std::endl;
    // std::cout << "destRect.y  ->   " << destRect.y << std::endl;
    // std::cout << "destRect.w  ->   " << destRect.w << std::endl;
    // std::cout << "destRect.h  ->   " << destRect.h << std::endl;


    SDL_RenderCopyEx( pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip );

}


//Instance_GameSDL::Instance()->GetCamera()
// RENDERING TILED LAYER WITH ANIMATION
// *** NOTE THAT THIS FUNCTION EXCUTES IN THE FOR LOOP IN LayerTile OBJECT ***
void ManagerTexture::RenderTile(	std::string id, 
									int margin, 
									int spacing, 
									int x, 
									int y, 
									int width, 
									int height, 
                                    int scale,
									int currentRow, 
									int currentFrame, 
									SDL_Renderer *pRenderer) {

    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    
    srcRect.w = width;
    srcRect.h = height;    

    destRect.w = width * scale;
    destRect.h = height * scale;


	//destRect.x = x  - (int) Instance_GameSDL::Instance()->GetCamera()->x;
    //destRect.y = y - (int) Instance_GameSDL::Instance()->GetCamera()->y;
   
    destRect.x = x * scale - (int) Instance_GameSDL::Instance()->GetCamera()->x;
    destRect.y = y * scale - (int) Instance_GameSDL::Instance()->GetCamera()->y;

    //destRect.x = x * 2;
    //destRect.y = y * 2; 


    SDL_RenderCopyEx(pRenderer,				m_textureMap[id],	&srcRect,					&destRect,						0,					0,		SDL_FLIP_NONE);
	//				 the rendering context	source texture		source SDL_Rect structure	destination SDL_Rect structure	angle in degrees	center	flipping actions
}


void ManagerTexture::ClearFromTextureMap( std::string id ) {
    m_textureMap.erase( id );
}



}
