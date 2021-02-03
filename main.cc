
#include "raytracing.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

//A function that colours a pixel according to the surface normal if a ray hits a sphere 
// double  hit_sphere(const point3& center, double radius, const ray& r) {
//     vec3 oc = r.origin() - center;
//     auto a = r.direction().length_squared();
//     auto half_b = dot(oc, r.direction());
//     auto c = oc.length_squared() - radius*radius;
//     auto discriminant = half_b*half_b - a*c;
//     if (discriminant < 0) {
//         return -1.0;
//      } else {
//         return (-half_b - sqrt(discriminant) ) / a;
//     }
// }

//A function for determining the colour of a ray
color ray_color(const ray& r, hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image properties
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width/aspect_ratio);

    //generate world properties
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

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
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone. \n";
}