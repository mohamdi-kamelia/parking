#include <SDL2/SDL.h>
//#define SDL_H
#include <iostream>


class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::string title;

public:
    Window(int w, int h, std::string t) : width(w), height(h), title(t) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Renderer* getRenderer() const {
        return renderer;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

int main(int argc, char *argv[]) {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const std::string WINDOW_TITLE = "SDL Window";

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Boucle principale des événements SDL
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&e) != 0) {
            // Si l'utilisateur ferme la fenêtre
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.getRenderer());

        // Dessiner ici

        // Mettre à jour l'affichage
        SDL_RenderPresent(window.getRenderer());
    }

    return 0;
}

