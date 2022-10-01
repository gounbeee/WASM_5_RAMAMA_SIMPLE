

// https://github.com/shlomnissan/sdl-wasm


#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <GameSDL.h>


#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

const unsigned int size = 64;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Point velocity = {0, 0};
SDL_Rect sprite = {0, 0, size, size};
SDL_Texture *texture = NULL;






const int FPS = 60;
const unsigned int DELAY_TIME = (unsigned int) (1000.0f / (float)FPS);

const int GAME_WIDTH = 800;
const int GAME_HEIGHT = 600;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Uint32 frameStart, frameTime;




extern "C" {



bool init() {
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    if (window == NULL | renderer == NULL) {
        return false;
    } 

    return true;
}





void load_textures() {
    SDL_Surface *surface = IMG_Load("resources/texture.png");
    if (!surface) {
        printf("%s\n", IMG_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x75, 0xFF, 0xFF));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}





void process_event(SDL_Event *event) {
    SDL_Keycode key = event->key.keysym.sym;
    
    if (event->key.type == SDL_KEYDOWN) {
        if (key == SDLK_LEFT || key == SDLK_RIGHT) {
            velocity.x = key == SDLK_LEFT ? -1 : 1;
        }
        if (key == SDLK_UP || key == SDLK_DOWN) {
            velocity.y = key == SDLK_UP ? -1 : 1;
        }
    }
    if (event->key.type == SDL_KEYUP) {
        velocity.x = 0;
        velocity.y = 0;
    }
}





void process_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        process_event(&event);
    }
}





void update() {
    sprite.x += velocity.x;
    sprite.y += velocity.y;
}




void draw() {
    SDL_RenderCopy(renderer, texture, NULL, &sprite);
}





void main_loop() {
    // process_input();

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);
    
    // update();
    // draw();    

    // SDL_RenderPresent(renderer);






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






void destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}





int main() {
    // init();
    // load_textures();

    // sprite.x = (WINDOW_WIDTH - size) / 2;
    // sprite.y = (WINDOW_HEIGHT - size) / 2;







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







    //destroy();


    return EXIT_SUCCESS;

}





}

