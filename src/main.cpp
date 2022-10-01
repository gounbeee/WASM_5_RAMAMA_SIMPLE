

// https://github.com/shlomnissan/sdl-wasm


#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <GameSDL.h>





const int FPS = 60;
const unsigned int DELAY_TIME = (unsigned int) (1000.0f / (float)FPS);

const int GAME_WIDTH = 800;
const int GAME_HEIGHT = 600;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Uint32 frameStart, frameTime;




extern "C" {


void main_loop() {


    frameStart = SDL_GetTicks();                                                // GETTING STARTING-TIME FOR "ONE FRAME"

    // GAME LOOP
    Instance_GameSDL::Instance()->HandlingEvents();                             // GAME LOOP 1 :: HANDLING EVENTS
    Instance_GameSDL::Instance()->Update();                                     // GAME LOOP 2 :: UPDATING STATES
    Instance_GameSDL::Instance()->Render();                                     // GAME LOOP 3 :: RENDERING SCREEN

    // TIMING CHECK 2/2
    // IMPLEMENT FIXED FRAME RATE
    frameTime = SDL_GetTicks() - frameStart;                                    // CALCULATING THE LENGTH OF TIME FOR ONE FRAME
    if( frameTime < DELAY_TIME ){                                               // IF LENGTH OF TIME FOR ONE FRAME IS LESS THAN WE WANT ( TOO FAST )
        SDL_Delay( (int) (DELAY_TIME - frameTime));                             // DELAY "MORE" FOR DIFFERENCES BETWEEN TIME FOR ONE FRAME AND THE NUMBER WE WANT
    }


}






int main() {

    // GAME INITIALIZATION

    Instance_GameSDL::Instance()->Initialize(   "RAMAMA ver 0.1" , 
                                                SDL_WINDOWPOS_CENTERED, 
                                                SDL_WINDOWPOS_CENTERED, 
                                                GAME_WIDTH, 
                                                GAME_HEIGHT, 
                                                SCREEN_WIDTH, 
                                                SCREEN_HEIGHT, 
                                                SDL_WINDOW_SHOWN);
    
    // CHECKING INITIALIZATION
    if( Instance_GameSDL::Instance()->GetInitFlag() ) {
        std::cout << "main() :: INITIALIZING GAME IS OK" << std::endl;                                                  // SUCCEEDED
    } else {                                                                                                                // IF IT IS FAILED
        std::cout << "main() :: INITIALIZING GAME FAILED WITH AN ERROR !!!! - " << SDL_GetError() << std::endl;         // PRINT THE ERROR WHEN INITIALIZATION OF GAME
        return -1;                                                                                                          // EXIT WITH "-1"
    }






    emscripten_set_main_loop(main_loop, -1, 1);





    // GAME CLEANING UP
    // QUIT THE APPLICATION
    Instance_GameSDL::Instance()->Quit();                                           // QUIT SDLs


    std::cout << "~~~~~~~~~~~~~~~~~~~~~~ QUIT APPLICATION ~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;    


    return EXIT_SUCCESS;

}







}

