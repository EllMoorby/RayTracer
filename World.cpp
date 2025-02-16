#include "World.h"

#include <vector>

#include "Ray.h"


World::World()
    : camera(vec3(0, 0, 0), 16.0f / 9.0f, 400, 1.0f),
    texture(),
    sprite(texture){

    texture = sf::Texture(sf::Vector2u(camera.image_width, camera.image_height));
}

void World::start() {
    sprite = sf::Sprite(texture);
    sprite.setTexture(texture);
    createWindow();
    render();
    while (window.isOpen()) {
        update();
        //test();
    }
    destroyWindow();
}

void World::createWindow() {
    window.create(sf::VideoMode(sf::Vector2u(camera.image_width, camera.image_height)), "RayTracer", sf::Style::Titlebar | sf::Style::Close);
}

void World::update() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }

    window.clear();
    render();
    window.draw(sprite);
    window.display();
}


void World::render() {
    for (int y = 0; y < camera.image_height; y++) {
        std::cout << "\rScanlines remaining: " << (camera.image_height - y) << ' ';
        for (int x = 0; x < camera.image_width; x++) {
            auto pixel_center = camera.pixel00_loc + (x * camera.pixel_delta_u) + (y * camera.pixel_delta_v);
            auto ray_direction = pixel_center - camera.location;
            Ray r(camera.location, ray_direction);

            sf::Color pixel_color = sf::Color((float(x) / camera.image_width) * 255, (float(y) / camera.image_height) * 255, 0);
            camera.setOutputImagePixel(x,y, pixel_color);
        }
    }
    texture.update(camera.getOutputImage());
}

void World::destroyWindow() {
    window.close();
}

void World::test() {

    sf::Image testImage = sf::Image(sf::Vector2u(camera.image_width, camera.image_height));
    sf::Texture testTexture = sf::Texture(testImage);
    sf::Sprite testSprite = sf::Sprite(testTexture);

    for (int y = 0; y < camera.image_height; y++) {
        for (int x = 0; x < camera.image_width; x++) {
            auto pixel_center = camera.pixel00_loc + (x * camera.pixel_delta_u) + (y * camera.pixel_delta_v);
            auto ray_direction = pixel_center - camera.location;
            Ray r(camera.location, ray_direction);

            sf::Color pixel_color = sf::Color(255, 0, 0);
            testImage.setPixel(sf::Vector2u(x,y),pixel_color);;
        }
    }
    testTexture.update(testImage);

    window.clear();
    window.draw(testSprite);
    window.display();
}


