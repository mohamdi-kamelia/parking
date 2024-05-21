#include "game_object.hpp"

GameObject::GameObject(int gridX, int gridY, SDL_Color color, SDL_Renderer* renderer, bool isHorizontal)
    : m_color(color), m_renderer(renderer), m_selected(false), m_isHorizontal(isHorizontal) {
    if (m_isHorizontal) {
        m_x = gridX * GRID_SIZE;
        m_y = gridY * GRID_SIZE;
        m_width = CAR_WIDTH;
        m_height = CAR_HEIGHT;
    } else {
        m_x = gridX * GRID_SIZE;
        m_y = gridY * GRID_SIZE;
        m_width = CAR_HEIGHT;
        m_height = CAR_WIDTH;
    }
}

void GameObject::render() {
    SDL_Rect rect = {m_x, m_y, m_width, m_height};
    SDL_Color renderColor = m_selected ? SDL_Color{255, 255, 255, 255} : m_color;
    SDL_SetRenderDrawColor(m_renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

bool GameObject::isAtPosition(int x, int y) {
    return (x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height);
}

void GameObject::select() { m_selected = true; }
void GameObject::deselect() { m_selected = false; }
bool GameObject::isSelected() { return m_selected; }

bool GameObject::canMove(int dx, int dy, const std::vector<GameObject>& others) {
    if ((m_isHorizontal && dy != 0) || (!m_isHorizontal && dx != 0)) {
        return false;
    }

    int newX = m_x + dx * GRID_SIZE;
    int newY = m_y + dy * GRID_SIZE;

    for (const auto& other : others) {
        if (&other != this) {
            if (!(newX + m_width <= other.m_x || newX >= other.m_x + other.m_width ||
                  newY + m_height <= other.m_y || newY >= other.m_y + other.m_height)) {
                return false;
            }
        }
    }

    if (m_color.r == 255 && m_color.g == 255 && m_color.b == 0) {
        if (newX + m_width > WINDOW_WIDTH) {
            return true;
        }
    }

    return (newX >= 0 && newX + m_width <= WINDOW_WIDTH && newY >= 0 && newY + m_height <= WINDOW_HEIGHT);
}

void GameObject::move(int dx, int dy) {
    m_x += dx * GRID_SIZE;
    m_y += dy * GRID_SIZE;
}

bool GameObject::hasReachedRightEdge() const {
    return (m_color.r == 255 && m_color.g == 255 && m_color.b == 0) && (m_x + m_width >= WINDOW_WIDTH);
}
