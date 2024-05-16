#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "GameObject.hpp"

void printGrid(int grid[6][6], const std::vector<GameObject>& cars);
bool checkWin(const GameObject& car);
bool checkColisions(const std::vector<GameObject>& cars);

#endif