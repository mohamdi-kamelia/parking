#ifndef IMAGE_H
#define IMAGE_H

#include "GameObject.h"
#include <SDL2/SDL_image.h>
#include <string>

class Image : public GameObject {
private:
    SDL_Texture* texture;

public:
    Image(int x, int y, int width, int height, const std::string& imagePath, SDL_Renderer* renderer)
        : GameObject(x, y, width, height), texture(nullptr) {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        if (!surface) {
            std::cerr << "Unable to load image " << imagePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    ~Image() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    void render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { x, y, width, height };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
};

#endif
