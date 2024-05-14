#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    else {
        std::cout << "SDL_Init Success" << std::endl;
    }
    SDL_Quit();
    return 0;
}