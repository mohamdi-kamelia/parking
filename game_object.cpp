#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 400;  // Taille de la fenêtre inchangée
const int WINDOW_HEIGHT = 400;
const int GRID_SIZE = 40;  // Taille de la grille principale pour les voitures
const int PIXELS_PER_CM = 30;  // Environ 1 cm en pixels

class GameObject {
public:
    GameObject(int gridX, int gridY, int gridWidth, int gridHeight, SDL_Color color, SDL_Renderer* renderer)
        : m_x(gridX * GRID_SIZE), m_y(gridY * GRID_SIZE), m_width(gridWidth * GRID_SIZE), m_height(gridHeight * GRID_SIZE),
          m_color(color), m_renderer(renderer), m_selected(false) {}

    void render() {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_Color renderColor = m_selected ? SDL_Color{255, 255, 255, 255} : m_color;  // Blanc si sélectionné
        SDL_SetRenderDrawColor(m_renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
        SDL_RenderFillRect(m_renderer, &rect);
    }

    bool isAtPosition(int x, int y) {
        return (x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height);
    }

    void select() { m_selected = true; }
    void deselect() { m_selected = false; }
    bool isSelected() { return m_selected; }

    bool canMove(int dx, int dy, const std::vector<GameObject>& others) {
        int newX = m_x + dx * GRID_SIZE;
        int newY = m_y + dy * GRID_SIZE;

        for (const auto& other : others) {
            if (&other != this) {
                if (!(newX + m_width <= other.m_x || newX >= other.m_x + other.m_width ||
                      newY + m_height <= other.m_y || newY >= other.m_y + other.m_height)) {
                    return false; // Détection de collision
                }
            }
        }
        return true; // Pas de collision
    }

    void move(int dx, int dy) {
        m_x += dx * GRID_SIZE;
        m_y += dy * GRID_SIZE;
    }

protected:
    int m_x, m_y, m_width, m_height;
    SDL_Color m_color;
    SDL_Renderer* m_renderer;
    bool m_selected;
};

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Couleur grise pour le quadrillage
    for (int x = 0; x < WINDOW_WIDTH; x += PIXELS_PER_CM) {
        for (int y = 0; y < WINDOW_HEIGHT; y += PIXELS_PER_CM) {
            SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);  // Lignes verticales
            SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);  // Lignes horizontales
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Parking Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::vector<GameObject> gameObjects;

    // Définir les voitures et les places de stationnement selon l'image
    gameObjects.emplace_back(2, 0, 3, 1, SDL_Color{0, 0, 255, 255}, renderer); // Voiture bleue horizontale (longue)
    gameObjects.emplace_back(3, 1, 1, 2, SDL_Color{0, 0, 255, 255}, renderer); // Voiture bleue verticale
    gameObjects.emplace_back(4, 3, 1, 3, SDL_Color{0, 0, 255, 255}, renderer); // Autre voiture bleue verticale
    gameObjects.emplace_back(1, 3, 2, 1, SDL_Color{255, 255, 0, 255}, renderer); // Voiture jaune horizontale (cible)

    GameObject* selectedObject = nullptr;

    // Boucle de jeu principale
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (selectedObject) {
                    selectedObject->deselect();
                    selectedObject = nullptr;
                }

                for (auto& gameObject : gameObjects) {
                    if (gameObject.isAtPosition(x, y)) {
                        selectedObject = &gameObject;
                        selectedObject->select();
                        break;
                    }
                }
            }

            if (selectedObject && event.type == SDL_KEYDOWN) {
                int dx = 0, dy = 0;
                switch (event.key.keysym.sym) {
                    case SDLK_UP: dy = -1; break;
                    case SDLK_DOWN: dy = 1; break;
                    case SDLK_LEFT: dx = -1; break;
                    case SDLK_RIGHT: dx = 1; break;
                }
                if (selectedObject->canMove(dx, dy, gameObjects)) {
                    selectedObject->move(dx, dy);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // Couleur de fond gris
        SDL_RenderClear(renderer);

        drawGrid(renderer); // Dessiner le quadrillage

        for (auto& gameObject : gameObjects) {
            gameObject.render();
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
