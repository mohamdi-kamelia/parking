#include <iostream>
#include "GameObject.hpp"
#include <vector>
#include "game.hpp"

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
