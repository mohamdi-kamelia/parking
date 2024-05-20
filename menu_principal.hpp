#ifndef MENU_PRINCIPAL_HPP
#define MENU_PRINCIPAL_HPP

#include <SDL2/SDL.h>
#include <string>
#include "constants.hpp"

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color);
Difficulty mainMenu(SDL_Renderer* renderer);

#endif // MENU_PRINCIPAL_HPP
