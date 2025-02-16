#include "Camera.h"

#include "vec3.h"

Camera::Camera(vec3 location, float aspect_ratio, unsigned int image_width, float focal_length = 1.0f) {
    // Calculate the image height, and ensure that it's at least 1.
    this->image_width = image_width;
    image_height = static_cast<unsigned int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Viewport widths less than one are ok since they are real valued.
    viewport_height = 2.0f;
    viewport_width = viewport_height * (double(image_width)/image_height);

    viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    viewport_upper_left = location - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    output_image = sf::Image(sf::Vector2u(image_width,image_height), sf::Color::White);
}

void Camera::setOutputImagePixel(unsigned int x,unsigned int y, sf::Color color) {
    output_image.setPixel(sf::Vector2u(x,y), color);
}

sf::Image Camera::getOutputImage() {
    return output_image;
}

