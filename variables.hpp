#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "game_object.hpp"
#include "constants.hpp"

extern std::vector<GameObject> gameObjects;
extern Difficulty currentDifficulty;
extern GameObject* selectedObject;
extern bool running;
extern bool gameWon;

#endif // VARIABLES_HPP
