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
    drawScreen();
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        drawScreen();
    }

}

bool World::hitSphere(const vec3 &center, float radius, const Ray &ray) {
    vec3 oc = center - ray.getOrigin();
    auto a = dot(ray.getDirection(), ray.getDirection());
    auto b = -2.0 * dot(ray.getDirection(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}


void World::drawScreen() {
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

            sf::Color pixel_color = rayColor(r);
            camera.setOutputImagePixel(x,y, pixel_color);
        }
    }
    texture.update(camera.getOutputImage());
}

void World::destroyWindow() {
    window.close();
}

sf::Color World::rayColor(const Ray& ray) {
    if (hitSphere(vec3(0,0,-1), 0.5, ray))
        return sf::Color(255, 0, 0);


    vec3 unit_direction = unit_vector(ray.getDirection());
    auto a = 0.5*(unit_direction.y() + 1.0);
    vec3 output_color = (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
    return sf::Color(output_color.x()*255,output_color.y()*255,output_color.z()*255);
}


