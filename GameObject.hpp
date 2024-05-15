#ifndef GameObject_hpp
#define GameObject_hpp
#include <string>

class GameObject {
    public:
        GameObject(int x, int y, int width, int height, std::string symbol);

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        std::string getSymbol() const;
        
    private:
        int x;
        int y;
        int width;
        int height;
        std::string symbol;
};

#endif