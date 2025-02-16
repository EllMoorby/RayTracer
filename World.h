#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <SFML\System.hpp>

#include "Camera.h"


class World {
public:
    World();

    void addSphere(vec3 location, float radius);
    void render();
    void start(); //Starts the program
    void createWindow();
    void update(); //Runs every frame
    void destroyWindow();
    void test();

private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    Camera camera;
};



#endif //WORLD_H
