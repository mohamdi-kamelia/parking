#include <iostream>
#include "GameObject.hpp"

void printGrid(int grid[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    int grid[6][6] = {0};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            grid[i][j] = 0;
        }
    }

    GameObject carX(0, 0, 2, 1);
    GameObject car1(6, 6, 1, 2);

    