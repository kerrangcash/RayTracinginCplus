#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //divide the colour by the number of samples
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    //write the translated [0,255] value for each colour component
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif