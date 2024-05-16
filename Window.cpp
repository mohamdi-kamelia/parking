#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

// Colors
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};

// Grid size
const int GRID_SIZE = 6;
const int CELL_SIZE = 100;

// Abstract class for game objects
class GameObject {
protected:
    int x, y, width, height;

public:
    GameObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void move(int dx, int dy, const std::vector<GameObject*>& obstacles) = 0;
    virtual bool contains(int px, int py) const = 0;
    virtual ~GameObject() {} // Virtual destructor

    // Access methods
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// Class representing a vehicle
class Vehicle : public GameObject {
private:
    SDL_Color color;

public:
    Vehicle(int x, int y, int width, int height, SDL_Color color)
        : GameObject(x, y, width, height), color(color) {}

    void draw(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderFillRect(renderer, &rect);
    }

    void move(int dx, int dy, const std::vector<GameObject*>& obstacles) override {
        if ((dx != 0 && dy != 0) || (dx != 0 && height > width) || (dy != 0 && width > height)) {
            return; // Quit the function without performing movement
        }

        // Calculate new positions
        int newX = x + dx;
        int newY = y + dy;

        // Check if the new position is valid
        if (newX >= 0 && newX + width <= GRID_SIZE * CELL_SIZE &&
            newY >= 0 && newY + height <= GRID_SIZE * CELL_SIZE) {
            // Check collision with obstacles
            bool collision = false;
            for (const auto& obstacle : obstacles) {
                if (obstacle != this) {
                    if (newX < obstacle->getX() + obstacle->getWidth() &&
                        newX + width > obstacle->getX() &&
                        newY < obstacle->getY() + obstacle->getHeight() &&
                        newY + height > obstacle->getY()) {
                        collision = true;
                        break;
                    }
                }
            }

            // If no collision, perform movement
            if (!collision) {
                x = newX;
                y = newY;
            }
        }
    }

    bool contains(int px, int py) const override {
        return (px >= x && px <= x + width && py >= y && py <= y + height);
    }

    SDL_Color getColor() const { return color; }
};

// Class managing the SDL window
class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;

public:
    Window(int w, int h, std::string t) : width(w), height(h) {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Create SDL window
        window = SDL_CreateWindow(t.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Create SDL renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Renderer* getRenderer() const {
        return renderer;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

// Main function
int main(int argc, char *argv[]) {
    const int SCREEN_WIDTH = GRID_SIZE * CELL_SIZE;
    const int SCREEN_HEIGHT = GRID_SIZE * CELL_SIZE;
    const std::string WINDOW_TITLE = "SDL Parking";

    // Create SDL window
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // List of game objects
    std::vector<GameObject*> objects;

    // Add vehicles
    objects.push_back(new Vehicle(2 * CELL_SIZE, 0, CELL_SIZE, 3 * CELL_SIZE, RED));
    objects.push_back(new Vehicle(0, 4 * CELL_SIZE, 3 * CELL_SIZE, CELL_SIZE, YELLOW));
    objects.push_back(new Vehicle(3 * CELL_SIZE, 4 * CELL_SIZE, CELL_SIZE, 3 * CELL_SIZE, BLUE));
    objects.push_back(new Vehicle(4 * CELL_SIZE, 3 * CELL_SIZE, CELL_SIZE, 2 * CELL_SIZE, BLUE));

    // Variable to track the index of the selected vehicle
    int selectedVehicleIndex = -1; // initialize to -1 (no vehicle selected)

    // Main SDL event loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Handle mouse click events for vehicle selection
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                for (size_t i = 0; i < objects.size(); ++i) {
                    if (objects[i]->contains(mouseX, mouseY)) {
                        selectedVehicleIndex = i;
                        break;
                    }
                }
            } else if (e.type == SDL_KEYDOWN) {
                // Handle key events for vehicle movement
                if (selectedVehicleIndex != -1) {
                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            objects[selectedVehicleIndex]->move(0, -CELL_SIZE, objects);
                            break;
                        case SDLK_DOWN:
                            objects[selectedVehicleIndex]->move(0, CELL_SIZE, objects);
                            break;
                        case SDLK_LEFT:
                            objects[selectedVehicleIndex]->move(-CELL_SIZE, 0, objects);
                            break;
                        case SDLK_RIGHT:
                            objects[selectedVehicleIndex]->move(CELL_SIZE, 0, objects);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
         // Clear the screen
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(window.getRenderer());

        // Draw grid lines
        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
        for (int i = 1; i < GRID_SIZE; ++i) {
            SDL_RenderDrawLine(window.getRenderer(), i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
            SDL_RenderDrawLine(window.getRenderer(), 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
        }
        // Draw game objects
        for (const auto& object : objects) {
            object->draw(window.getRenderer());
        }

        // Update display
        SDL_RenderPresent(window.getRenderer());
    }

    // Clean up memory
    for (auto& object : objects) {
        delete object;
    }

    return 0;
}
