#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Colors in CG (computer graphics) are made up of three colors
// RGB. Different proportions of these colors make a single colors.
// For eg: an X color can be defined as (0.15, 0.25, 0.45)
using color = vec3;

// We are going to transform our data into gamma space so that our image viewer
// can more accurately display our image. As a simple approximation, we can use
// “gamma 2” as our transform
inline double linear_to_gamma(double linear_component)
{
    return std::sqrt(linear_component);
}

double clamp(double x, double min, double max)  {
        if (x < min) return min;
        if (x > max) return max;
        return x;
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();


    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Translate the [0,1] component values to the byte range [0,255].
    // The PPM image we create is a 256*256. Translating the values to
    // that range helps us define the intensity of each color.
    double clamp_min = 0.000;
    double clamp_max = 0.999;
    int rbyte = int(256 * clamp(r, clamp_min, clamp_max));
    int gbyte = int(256 * clamp(g, clamp_min, clamp_max));
    int bbyte = int(256 * clamp(b, clamp_min, clamp_max));

    // Write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}

#endif