#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
void GameObject::moveHorizontaly() {
    this->x += 1;
}
void GameObject::moveVertically() {
    this->y += 1;
}