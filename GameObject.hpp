#ifndef GameObject_hpp
#define GameObject_hpp

class GameObject {
    public:
        GameObject(int x, int y, int width, int height);

        void moveHorizontaly();
        void moveVertically();
        
    private:
        int x;
        int y;
        int width;
        int height;
};

#endif