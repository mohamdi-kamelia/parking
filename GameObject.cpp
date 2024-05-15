#include "GameObject.hpp"
#include <iostream>
#include <string>

GameObject::GameObject(int x, int y, int width, int height, std::string symbol) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->symbol = symbol;
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
std::string GameObject::getSymbol() const {
    return this->symbol;
}