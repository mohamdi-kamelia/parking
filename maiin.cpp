#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "constants.hpp"
#include "variables.hpp"
#include "game_object.hpp"
#include "menu_principal.hpp"

void drawFence(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    int fenceWidth = 10;

    // Dessiner le cadre de la clôture
    SDL_Rect fenceRect = {0, 0, WINDOW_WIDTH, fenceWidth};  // Haut
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect.y = WINDOW_HEIGHT - fenceWidth;  // Bas
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect = {0, 0, fenceWidth, WINDOW_HEIGHT};  // Gauche
    SDL_RenderFillRect(renderer, &fenceRect);

    // Droite, sans l'ouverture pour la voiture jaune
    int openingHeight = CAR_HEIGHT;
    fenceRect = {WINDOW_WIDTH - fenceWidth, 0, fenceWidth, (WINDOW_HEIGHT / 2) - (openingHeight / 2)};
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect.y = (WINDOW_HEIGHT / 2) + (openingHeight / 2);
    fenceRect.h = WINDOW_HEIGHT - fenceRect.y;
    SDL_RenderFillRect(renderer, &fenceRect);
}

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int x = 0; x < WINDOW_WIDTH; x += PIXELS_PER_CM) {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int y = 0; y < WINDOW_HEIGHT; y += PIXELS_PER_CM) {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
}

void loadLevel(std::vector<GameObject>& gameObjects, SDL_Renderer* renderer, Difficulty difficulty) {
    gameObjects.clear();

    if (difficulty == EASY) {
        gameObjects.emplace_back(2, 1, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(3, 2, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(4, 3, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(1, 3, SDL_Color{255, 255, 0, 255}, renderer, true);  // Voiture jaune
    } else if (difficulty == MEDIUM) {
        gameObjects.emplace_back(1, 1, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(2, 1, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(3, 2, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(4, 3, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(1, 5, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(1, 3, SDL_Color{255, 255, 0, 255}, renderer, true);  // Voiture jaune
    } else if (difficulty == HARD) {
        gameObjects.emplace_back(4, 1, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(1, 1, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(2, 2, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(3, 6, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(4, 0.5, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(1, 2, SDL_Color{0, 0, 255, 255}, renderer, true);
        gameObjects.emplace_back(4, 7, SDL_Color{0, 0, 255, 255}, renderer, false);
        gameObjects.emplace_back(1, 3, SDL_Color{255, 255, 0, 255}, renderer, true);  // Voiture jaune
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Parking Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Difficulty selectedDifficulty = mainMenu(renderer, nullptr);

    std::vector<GameObject> gameObjects;
    loadLevel(gameObjects, renderer, selectedDifficulty);

    bool running = true;
    GameObject* selectedObject = nullptr;
    Uint32 yellowCarExitTime = 0;  // Temps de sortie de la voiture jaune

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (selectedObject) {
                    selectedObject->deselect();
                    selectedObject = nullptr;
                }

                for (auto& gameObject : gameObjects) {
                    if (gameObject.isAtPosition(x, y)) {
                        selectedObject = &gameObject;
                        selectedObject->select();
                        break;
                    }
                }
            }

            if (selectedObject && event.type == SDL_KEYDOWN) {
                int dx = 0, dy = 0;
                switch (event.key.keysym.sym) {
                    case SDLK_UP: dy = -1; break;
                    case SDLK_DOWN: dy = 1; break;
                    case SDLK_LEFT: dx = -1; break;
                    case SDLK_RIGHT: dx = 1; break;
                }
                if (selectedObject->canMove(dx, dy, gameObjects)) {
                    selectedObject->move(dx, dy);
                }
            }
        }

        // Vérifier si la voiture jaune a atteint le bord droit
        for (const auto& obj : gameObjects) {
            if (obj.hasReachedRightEdge()) {
                yellowCarExitTime = SDL_GetTicks();  // Enregistrer le temps de sortie
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);  // Set background color
        SDL_RenderClear(renderer);

        drawGrid(renderer);
        drawFence(renderer);

        for (auto& gameObject : gameObjects) {
            gameObject.render();
        }

        SDL_RenderPresent(renderer);
    }

    if (yellowCarExitTime != 0) {
        SDL_Delay(3000);  // Attendre 3 secondes avant de fermer
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
