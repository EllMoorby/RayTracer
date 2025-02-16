#include "Ray.h"

#include "vec3.h"

Ray::Ray(const vec3& origin, const vec3& direction) {
    this->origin = origin;
    this->direction = direction;
}

const vec3& Ray::getDirection() const {
    return direction;
}
const vec3& Ray::getOrigin() const {
    return origin;
}

vec3 Ray::at(double t) const {
    return origin + t * direction;
}

