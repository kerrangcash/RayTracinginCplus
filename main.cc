#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

//A function that colours a pixel red if a ray hits a sphere 
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

//A function for determining the colour of a ray
color ray_color(const ray& r) {

    //colour change if a sphere is hit
    if(hit_sphere(point3(0,0,-1), 0.5, r)) {
        return color(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image properties
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width/aspect_ratio);

    //camera properties
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal_axis = vec3(viewport_width, 0, 0);
    auto vertical_axis = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal_axis/2 - vertical_axis/2 - vec3(0, 0, focal_length);

    //Render

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    //writes rows of pixels from top to bottom
    for (int i = img_height-1; i>= 0; --i) {

        // progress indicator
        std::cerr << "\rSclanlines remaining: " << i << ' ' << std::flush;

        //writes rows of pixels from left to right
        for (int j = 0; j < img_width; ++j) {
            auto u = double(j) / (img_width-1);
            auto v = double(i) / (img_height-1);
            ray r(origin, lower_left_corner + u*horizontal_axis + v*vertical_axis - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone. \n";
}