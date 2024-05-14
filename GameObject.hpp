#ifndef GameObject_hpp
#define GameObject_hpp

class GameObject {
    public:
        GameObject(int x, int y, int width, int height);

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        
    private:
        int x;
        int y;
        int width;
        int height;
};

#endif