#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include <SFML/Graphics.hpp>


class Camera {
    public:
    Camera(vec3 location, float aspect_ratio,unsigned int image_width, float focal_length);
    double aspect_ratio;
    unsigned int image_width;
    unsigned int image_height;

    vec3 location;

    double viewport_width;
    double viewport_height;

    vec3 viewport_u;
    vec3 viewport_v;

    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 viewport_upper_left;
    vec3 pixel00_loc;

    void setOutputImagePixel(unsigned int x,unsigned int y, sf::Color color);
    sf::Image getOutputImage();
    private:
    sf::Image output_image;
};



#endif //CAMERA_H
