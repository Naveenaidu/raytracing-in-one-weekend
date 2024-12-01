#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Colors in CG (computer graphics) are made up of three colors
// RGB. Different proportions of these colors make a single colors.
// For eg: an X color can be defined as (0.15, 0.25, 0.45)
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    // The PPM image we create is a 256*256. Translating the values to
    // that range helps us define the intensity of each color.
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}

#endif