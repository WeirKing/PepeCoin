
//SDL2 flashing random color example
//Should work on iOS/Android/Mac/Windows/Linux

#include    <SDL2/SDL.h>
#include    <SDL2/SDL_opengl.h>
#include    <iostream>

using namespace std;

SDL_Window *window;
SDL_Surface *screen;
enum color {red, blue, green, purple};

int create_window(){
	SDL_DisplayMode current;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GetCurrentDisplayMode(0, &current);
	if (current.w < 840 or current.h < 640){
		cout << "You don't have the required screen resolution to play this game \
		(minimum of 840x640)\n";
	}
	window = SDL_CreateWindow("the game", current.w/2 - 400, current.h/2 - 300, 800, 600, 0);
	if (window == NULL){
		printf("Could not get window:%s \n", SDL_GetError());
		return 1;
	}
	screen = SDL_GetWindowSurface(window);
	if (screen == NULL){
		cout << "error making window\n";
		return 1;
	}
	return 0;
}

SDL_Surface* load_media(string file){
	SDL_Surface *surface = new SDL_Surface;
	surface = SDL_LoadBMP(file.c_str());
	if (surface == NULL){
		cout << "file does not contain valid image or other error in image loading\n";
		free(surface);
		return surface;
	}
	return surface;
}
int main(){
	create_window();
    printf("♢\n");
    SDL_Event event;
    SDL_Surface *image = load_media("images/sprites.bmp");
    if (screen == NULL){
    	cout << "fuck\n";
    }
    bool is_running = true;
    while (is_running){
        while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				is_running = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						if (SDL_BlitSurface(image, NULL, screen, NULL)){
							cout << SDL_GetError() << endl;
						}
				}

			}
        }
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
}
