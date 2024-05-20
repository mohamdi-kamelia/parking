#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int GRID_SIZE = 40;  // Taille d'un bloc de la grille
const int PIXELS_PER_CM = 30;  // Taille d'un cm en pixels pour le quadrillage
const int CAR_WIDTH = 2 * GRID_SIZE;  // Largeur uniforme pour toutes les voitures
const int CAR_HEIGHT = GRID_SIZE;  // Hauteur uniforme pour toutes les voitures

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

#endif // CONSTANTS_HPP