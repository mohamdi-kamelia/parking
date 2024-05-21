#include <iostream>
#include <vector>

class ParkingGame {
private:
    std::vector<std::vector<char>> grille;

public:

    ParkingGame() : grille(6, std::vector<char>(6, '_')) {}

 
    void afficherGrille() {
        std::cout << "  1 2 3 4 5 6" << std::endl;
        char ligneLabel = 'A';
        for (const auto& ligne : grille) {
            std::cout << ligneLabel++ << " ";
            for (char caseGrille : ligne) {
                std::cout << caseGrille << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ParkingGame jeu;

    // Affichage de la grille
    jeu.afficherGrille();

    return 0;
}
