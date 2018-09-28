
//SDL2 flashing random color example
//Should work on iOS/Android/Mac/Windows/Linux

#include    <SDL2/SDL.h>
#include    <SDL2/SDL_opengl.h>
#include    <iostream>

using namespace std;


int main(){
    SDL_Init(SDL_INIT_VIDEO);


    SDL_Window *window;
    window = SDL_CreateWindow("the game", 100, 100, 600, 450, 0);

    if (window == NULL){
        printf("Could not get window:%s \n", SDL_GetError());
        return 1;
    }
    printf("♢\n");
    SDL_Event event;

    bool is_running = true;
    while (is_running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                is_running = false;
            }
        }
        SDL_Delay(16);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
}
