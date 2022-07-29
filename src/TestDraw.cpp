// C++ Standard Libraries
#include <iostream>
// Third party
#include <SDL.h>
// Project files
#include "Utility_SDL.h"

int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Grab the window surface.
    SDL_Surface* screen;

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",
            350,
            100,
            1080,
            960,
            SDL_WINDOW_SHOWN);
    
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* SDL_Surface* surface = SDL_LoadBMP("./images/test.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); */

    // Create a rectangle
    SDL_FRect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 400;
    rectangle.h = 400;
    SDL_FRect rectangleF;
    rectangleF.x = 400;
    rectangleF.y = 250;
    rectangleF.w = 200;
    rectangleF.h = 350;
    SDL_FRect result;
    SDL_IntersectFRect(&rectangle, &rectangleF, &result);

    // Infinite loop for our application
    bool simIsRunning = true;
    // Main application loop
    while(simIsRunning){
        SDL_Event event;
        
        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x,&y);

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                simIsRunning= false;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    simIsRunning = false;
                }
            }
            
        }
        // (2) Handle Updates

        // (3) Clear Draw the Screen
        // Gives us a clear canvas
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        
        
        // Do our drawing
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 5, 5, 100, 120);
        SDL_Utility::DrawCircle(renderer, 300, 50, 50);
        SDL_Utility::DrawCircle(renderer, 300, 200, 120);

        for(int i = 175; i < 300; i++){
            SDL_Utility::DrawCircle(renderer, 400, 400, i);
        }


        SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRectF(renderer, &rectangle);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRectF(renderer, &rectangleF);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRectF(renderer, &result);
        SDL_RenderFillRectF(renderer, &result);

        SDL_Utility::DrawRingF(renderer, 505.1, 456.789, 168.945, 10);

        // Finally show what we've drawn 
        SDL_RenderPresent(renderer);
    

    }

    // SDL_DestroyTexture(texture);
    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;

};