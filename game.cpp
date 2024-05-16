#include "game.hpp"
#include "GameObject.hpp"
#include <iostream>

void printGrid(int grid[6][6], const std::vector<GameObject>& cars) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            std::string isCar = ".";
            for (const auto& car : cars) {
                int carX = car.getX();
                int carY = car.getY();
                int carWidth = car.getWidth();
                int carHeight = car.getHeight();
                std::string carSymbol = car.getSymbol();
                
                // Check if the current cell is within the bounds of the car
                if (i >= carY && i < carY + carHeight && j >= carX && j < carX + carWidth) {
                    isCar = car.getSymbol();
                    break;
                }
            }
            std::cout << isCar << " ";
        }
        std::cout << std::endl;
    }
}
bool checkWin(const GameObject& carX) {
    if (carX.getWidth() > carX.getHeight()) {
        if (carX.getX() == 4 && carX.getWidth() == 2) {
            return true;
        }
        else if (carX.getX() == 3 && carX.getWidth() == 3) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (carX.getY() == 4 && carX.getHeight() == 2) {
            return true;
        }
        else if (carX.getY() == 3 && carX.getHeight() == 3) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool checkColisions(const std::vector<GameObject>& cars) {
    for (const auto& car : cars) {
        if (car.getX() < 0 || car.getX() + car.getWidth() > 6 ||
            car.getY() < 0 || car.getY() + car.getHeight() > 6) {
            return true;
        }
    }

    for (const auto& car1 : cars) {
        for (const auto& car2 : cars) {
            if (car1.getSymbol() != car2.getSymbol()) {
                if (car1.getX() < car2.getX() + car2.getWidth() &&
                    car1.getX() + car1.getWidth() > car2.getX() &&
                    car1.getY() < car2.getY() + car2.getHeight() &&
                    car1.getY() + car1.getHeight() > car2.getY()) {
                    return true;
                }
            }
        }
    }
    return false;
}
