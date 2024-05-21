#include "variables.hpp"

std::vector<GameObject> gameObjects;
Difficulty currentDifficulty = EASY;
GameObject* selectedObject = nullptr;
bool running = true;
bool gameWon = false;
