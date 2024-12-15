#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "rtweekend.h"

// A vector class that will store coordinates(point3) or the values of color
class vec3  {
    public:
        double e[3];

        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t){
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }   

        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        

        

};

// point3 is just a type alias for vec3, but useful for geometric clarity in the code
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}


inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}


// a = a1i + a2j + a3k
// b = b1i + b2j + b3k
// a X b =  i(a2b3 - a3b2) - j(a1b3 - a3b1) + k(a1b2 -a2b1)
// Ref: https://www.cuemath.com/geometry/cross-product/
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector(){
    while(true){
        // Pick a random point inside the cube enclosing the unit sphere (that is, where x, y, and z are all in the range [−1,+1])
        auto p = vec3::random(-1, 1);
        auto p_lensq = p.length_squared();
        if ( p_lensq <= 1) {
            return p / p.length();
        }

    }
}

// Return back the vector on the correct hemisphere
inline vec3 random_on_hemisphere(const vec3& normal){
    auto unit_vector = random_unit_vector();
    if (dot(normal, unit_vector) >= 0) 
        return unit_vector;
    else
        return -unit_vector;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}


#endif