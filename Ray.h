#ifndef RAY_H
#define RAY_H
#include <SFML/System/Vector3.hpp>

#include "vec3.h"


class Ray {
    public:
    Ray();
    Ray(const vec3& origin, const vec3& direction);
    const vec3& getOrigin() const;
    const vec3& getDirection() const;
    vec3 at(double t) const;
    private:
    vec3 origin;
    vec3 direction;
};



#endif //RAY_H
