#include "menu_principal.hpp"

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
    // This is a placeholder for real text rendering
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int textWidth = 10 * text.length();  // Approximate width of the text
    int textHeight = 24;  // Approximate height of the text
    SDL_Rect rect = {x, y, textWidth, textHeight};
    SDL_RenderFillRect(renderer, &rect);
}

void renderButton(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

Difficulty mainMenu(SDL_Renderer* renderer, SDL_Texture* backgroundTexture) {
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

        


        // Render buttons with different colors
        renderButton(renderer, 100, 100, 200, 50, SDL_Color{0, 0, 128, 255});  // Blue for Easy
        renderButton(renderer, 100, 200, 200, 50, SDL_Color{255, 165, 0, 255}); // Orange for Medium
        renderButton(renderer, 100, 300, 200, 50, SDL_Color{255, 0, 0, 255});   // Red for Hard

        SDL_RenderPresent(renderer);
    }

    return selectedDifficulty;
}
