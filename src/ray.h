#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private:
        point3 orig;
        vec3 dir;
    
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }

        // Ray equation at a certain point
        // Ray Equation = P(t) = A + tb
        // P = 3D position, A = ray origin, b = ray direction
        point3 at(double t) const {
            return orig + t*dir;
        }

};

#endif