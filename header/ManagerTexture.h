
#ifndef INCLUDE_GUARD_MANAGERTEXTURE_H
#define INCLUDE_GUARD_MANAGERTEXTURE_H


#include <map>
#include <SDL_image.h>
#include <iostream>

#include "GlobalSettings.h"


class ManagerTexture {

public:

    // MAKING SINGLETON
    static ManagerTexture* Instance(){
        // CHECKING THE INSTANCE ALREADY MADE
        if( s_pInstance == 0 ){                         // IF THERE IS NO INSTANCE, THEN MAKE NEW ONE
            s_pInstance = new ManagerTexture();
            return s_pInstance;
        }

        // THERE IS INSTANCE ALREADY MADE, JUST RETURN THAT
        return s_pInstance;
    }


    bool Load( std::string fileName, std::string id, SDL_Renderer* pRenderer );

    // DRAW FUNCTION 1 : draw()
    void Render( std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );


    // DRAW FUNCTION 2 : drawFrame()
    void RenderFrame( 
        std::string id, 
        int x, 
        int y, 
        int width, 
        int height, 
        int currentColumn, 
        int currentRow,  
        int currentFrame, 
        int scale,
        SDL_Renderer* pRenderer, 
        SDL_RendererFlip flip = SDL_FLIP_NONE );

	void RenderTile(  std::string id,
                    int margin,
                    int spacing,
                    int x,
                    int y,
                    int width,
                    int height,
                    int scale,
                    int currentRow,
                    int currentFrame,
                    SDL_Renderer *pRenderer);

	void ClearFromTextureMap( std::string id );

    std::map<std::string, SDL_Texture*> GetTextureMaps() const { return m_textureMap; }


private:

    // BELOW MAKES THIS CLASS TO SINGLETON
    // SO IT CANNOT BE CREATED PUBLIC SCOPE, ONLE CAN BE CREATED USING INSTANT FUNCTIONS Instance()
    ManagerTexture();

    ~ManagerTexture();


    // std::map of pointers to the SDL_Texture objects
    std::map<std::string, SDL_Texture*> m_textureMap;


    static ManagerTexture* s_pInstance;

};


typedef ManagerTexture Instance_ManagerTexture;


#endif
