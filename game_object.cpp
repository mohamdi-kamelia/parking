#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int GRID_SIZE = 40; // Taille d'un bloc de la grille
const int PIXELS_PER_CM = 30;  // Taille d'un cm en pixels pour le quadrillage
const int CAR_WIDTH = 2 * GRID_SIZE;  // Largeur uniforme pour toutes les voitures
const int CAR_HEIGHT = GRID_SIZE;     // Hauteur uniforme pour toutes les voitures

class GameObject {
public:
    GameObject(int gridX, int gridY, SDL_Color color, SDL_Renderer* renderer, bool isHorizontal)
        : m_color(color), m_renderer(renderer), m_selected(false), m_isHorizontal(isHorizontal) {
        if (m_isHorizontal) {
            m_x = gridX * GRID_SIZE;
            m_y = gridY * GRID_SIZE;
            m_width = CAR_WIDTH;  // Utilise la largeur uniforme
            m_height = CAR_HEIGHT;
        } else {
            m_x = gridX * GRID_SIZE;
            m_y = gridY * GRID_SIZE;
            m_width = CAR_HEIGHT; // Utilise la hauteur pour la largeur en orientation verticale
            m_height = CAR_WIDTH; // Utilise la largeur pour la hauteur en orientation verticale
        }
    }

    void render() {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_Color renderColor = m_selected ? SDL_Color{255, 255, 255, 255} : m_color;
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
        if ((m_isHorizontal && dy != 0) || (!m_isHorizontal && dx != 0)) {
            return false; // Empêche le mouvement perpendiculaire à l'orientation
        }

        int newX = m_x + dx * GRID_SIZE;
        int newY = m_y + dy * GRID_SIZE;

        for (const auto& other : others) {
            if (&other != this) {
                if (!(newX + m_width <= other.m_x || newX >= other.m_x + other.m_width ||
                      newY + m_height <= other.m_y || newY >= other.m_y + other.m_height)) {
                    return false; // Collision détectée
                }
            }
        }

        // Permettre à la voiture jaune de sortir par la droite
        if (m_color.r == 255 && m_color.g == 255 && m_color.b == 0) { // Vérifie que c'est la voiture jaune
            if (newX + m_width > WINDOW_WIDTH) {
                return true;
            }
        }

        return (newX >= 0 && newX + m_width <= WINDOW_WIDTH && newY >= 0 && newY + m_height <= WINDOW_HEIGHT);
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
    bool m_isHorizontal;
};

void drawFence(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    int fenceWidth = 10;

    // Dessiner le cadre de la clôture
    SDL_Rect fenceRect = {0, 0, WINDOW_WIDTH, fenceWidth};  // Haut
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect.y = WINDOW_HEIGHT - fenceWidth;  // Bas
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect = {0, 0, fenceWidth, WINDOW_HEIGHT};  // Gauche
    SDL_RenderFillRect(renderer, &fenceRect);

    // Droite, sans l'ouverture pour la voiture jaune
    int openingHeight = CAR_HEIGHT;
    fenceRect = {WINDOW_WIDTH - fenceWidth, 0, fenceWidth, (WINDOW_HEIGHT / 2) - (openingHeight / 2)};
    SDL_RenderFillRect(renderer, &fenceRect);
    fenceRect.y = (WINDOW_HEIGHT / 2) + (openingHeight / 2);
    fenceRect.h = WINDOW_HEIGHT - fenceRect.y;
    SDL_RenderFillRect(renderer, &fenceRect);
}

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int x = 0; x < WINDOW_WIDTH; x += PIXELS_PER_CM) {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int y = 0; y < WINDOW_HEIGHT; y += PIXELS_PER_CM) {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
}

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int textWidth = 10 * text.length(); // Approximate width of the text
    int textHeight = 24; // Approximate height of the text
    SDL_Rect rect = {x, y, textWidth, textHeight};
    SDL_RenderFillRect(renderer, &rect);
}

void addNewCar(std::vector<GameObject>& gameObjects, SDL_Renderer* renderer) {
    static int newCarCount = 0;
    SDL_Color color = {255, 0, 0, 255}; // Nouvelle voiture rouge
    bool isHorizontal = (newCarCount % 2 == 0); // Alternance entre horizontale et verticale
    gameObjects.emplace_back(newCarCount % 5, newCarCount % 5, color, renderer, isHorizontal);
    newCarCount++;
}

void resetGame(std::vector<GameObject>& gameObjects, SDL_Renderer* renderer) {
    gameObjects.clear();
    gameObjects.emplace_back(2, 1, SDL_Color{0, 0, 255, 255}, renderer, true);
    gameObjects.emplace_back(3, 2, SDL_Color{0, 0, 255, 255}, renderer, false);
    gameObjects.emplace_back(4, 3, SDL_Color{0, 0, 255, 255}, renderer, false);
    gameObjects.emplace_back(1, 3, SDL_Color{255, 255, 0, 255}, renderer, true);  // Voiture jaune
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Parking Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::vector<GameObject> gameObjects;
    resetGame(gameObjects, renderer);

    GameObject* selectedObject = nullptr;
    bool running = true;
    bool gameWon = false;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (gameWon) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;
                    if (x >= 150 && x <= 250 && y >= 300 && y <= 350) {
                        gameWon = false;
                        addNewCar(gameObjects, renderer);
                    }
                }
                continue;
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
                    if (selectedObject->isAtPosition(WINDOW_WIDTH, selectedObject->isAtPosition(0, selectedObject->isAtPosition(0, 0)) ? 0 : WINDOW_HEIGHT)) {
                        gameWon = true;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // Set background color
        SDL_RenderClear(renderer);

        drawGrid(renderer);
        drawFence(renderer);

        for (auto& gameObject : gameObjects) {
            gameObject.render();
        }

        if (gameWon) {
            renderText(renderer, "Partie Gagnée!", 100, 150, SDL_Color{255, 255, 255, 255});
            renderText(renderer, "Continuer", 150, 300, SDL_Color{255, 255, 255, 255});
            SDL_Rect buttonRect = {150, 300, 100, 50};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &buttonRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
