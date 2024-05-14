#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
void GameObject::moveLeft() {
    this->x -= 1;
}
void GameObject::moveRight() {
    this->x += 1;
}
void GameObject::moveUp() {
    this->y -= 1;
}
void GameObject::moveDown() {
    this->y += 1;
}
int GameObject::getX() const {
    return this->x;
}
int GameObject::getY() const {
    return this->y;
}
int GameObject::getWidth() const {
    return this->width;
}
int GameObject::getHeight() const {
    return this->height;
}