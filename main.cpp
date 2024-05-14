#include <iostream>
#include "GameObject.hpp"
#include <vector>

void printGrid(int grid[6][6], const std::vector<GameObject>& cars) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            bool isCar = false;
            for (const auto& car : cars) {
                int carX = car.getX();
                int carY = car.getY();
                int carWidth = car.getWidth();
                int carHeight = car.getHeight();
                
                // Check if the current cell is within the bounds of the car
                if (i >= carX && i < carX + carWidth && j >= carY && j < carY + carHeight) {
                    isCar = true;
                    break;
                }
            }
            if (isCar) {
                std::cout << "X ";
            } else {
                std::cout << ". ";
            }
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
    
    std::vector<GameObject> cars;
    cars.push_back(carX);
    cars.push_back(car1);

    printGrid(grid, cars);
    return 0;
}
