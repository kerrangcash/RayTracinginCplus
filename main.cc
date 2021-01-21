#include "color.h"
#include "vec3.h"

#include <iostream>

int main() {
    // Image
    const int img_width = 256;
    const int img_height = 256;

    //Render

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    //writes rows of pixels from top to bottom
    for (int i = img_height-1; i>= 0; --i) {

        // progress indicator
        std::cerr << "\rSclanlines remaining: " << i << ' ' << std::flush;

        //writes rows of picxels from left to right
        for (int j = 0; j < img_width; ++j) {
            color pixel_color(double(j)/(img_width-1), double(i)/(img_height-1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone. \n";
}