#include <iostream>
#include "GameObject.hpp"
#include <vector>

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

int main(int argc, char* argv[]) {
    int grid[6][6] = {0};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            grid[i][j] = 0;
        }
    }

    GameObject carX(0, 0, 2, 1, "X");
    GameObject car1(4, 0, 1, 2, "1");
    GameObject car2(2, 2, 3, 1, "2");
    
    std::vector<GameObject> cars;
    cars.push_back(carX);
    cars.push_back(car1);
    cars.push_back(car2);

    printGrid(grid, cars);

    while (!checkWin(carX)) {

        std::string carToMove;
        std::string direction;

        std::cout << "Enter the car you want to move: ";
        std::cin >> carToMove;

        bool carFound = false;
        for (auto& car : cars) {
            if (car.getSymbol() == carToMove){
                carFound = true;
            if (car.getWidth() > car.getHeight()) {
                std::cout << "Enter the direction you want to move the car (left = L / right = R): ";
                std::cin >> direction;
                switch (direction[0]) {
                    case 'L':
                        car.moveLeft();
                        if (checkColisions(cars)) {
                            car.moveRight();
                            std::cout << "Invalid move" << std::endl;
                        }
                        break;
                    case 'R':
                        car.moveRight();
                        if (checkColisions(cars)) {
                            car.moveLeft();
                            std::cout << "Invalid move" << std::endl;
                        }
                        break;
                    default:
                        std::cout << "Invalid direction" << std::endl;
                    }
                }
            else {
                std::cout << "Enter the direction you want to move the car (up = U / down = D): ";
                std::cin >> direction;
                    switch (direction[0]) {
                        case 'U':
                            car.moveUp();
                            if (checkColisions(cars)) {
                                car.moveDown();
                                std::cout << "Invalid move" << std::endl;
                            }
                            break;
                        case 'D':
                            car.moveDown();
                            if (checkColisions(cars)) {
                                car.moveUp();
                                std::cout << "Invalid move" << std::endl;
                            }
                            break;
                        default:
                            std::cout << "Invalid direction" << std::endl;
                    }
            }
            if (car.getSymbol() == "X") {
                carX = car;
            }
            }
            
        }        
        printGrid(grid, cars);
        if (!carFound) {
                std::cout << "Car not found" << std::endl;
        }
    }
    std::cout << "You win!" << std::endl;    
    return 0;
}
