#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "constants.hpp"

class GameObject {
public:
    GameObject(int gridX, int gridY, SDL_Color color, SDL_Renderer* renderer, bool isHorizontal);
    void render();
    bool isAtPosition(int x, int y);
    void select();
    void deselect();
    bool isSelected();
    bool canMove(int dx, int dy, const std::vector<GameObject>& others);
    void move(int dx, int dy);

protected:
    int m_x, m_y, m_width, m_height;
    SDL_Color m_color;
    SDL_Renderer* m_renderer;
    bool m_selected;
    bool m_isHorizontal;
};

#endif // GAME_OBJECT_HPP
