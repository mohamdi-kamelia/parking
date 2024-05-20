#include "menu_principal.hpp"

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int textWidth = 10 * text.length();  // Approximate width of the text
    int textHeight = 24;  // Approximate height of the text
    SDL_Rect rect = {x, y, textWidth, textHeight};
    SDL_RenderFillRect(renderer, &rect);
}

Difficulty mainMenu(SDL_Renderer* renderer) {
    bool menuRunning = true;
    Difficulty selectedDifficulty = EASY;

    while (menuRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= 100 && x <= 300) {
                    if (y >= 100 && y <= 150) {
                        selectedDifficulty = EASY;
                        menuRunning = false;
                    } else if (y >= 200 && y <= 250) {
                        selectedDifficulty = MEDIUM;
                        menuRunning = false;
                    } else if (y >= 300 && y <= 350) {
                        selectedDifficulty = HARD;
                        menuRunning = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderText(renderer, "Select Difficulty", 100, 50, SDL_Color{255, 255, 0, 255});
        renderText(renderer, "Easy", 100, 100, SDL_Color{255, 255, 0, 255});
        renderText(renderer, "Medium", 100, 200, SDL_Color{255, 255, 0, 255});
        renderText(renderer, "Hard", 100, 300, SDL_Color{255, 255, 0, 255});

        SDL_RenderPresent(renderer);
    }

    return selectedDifficulty;
}
