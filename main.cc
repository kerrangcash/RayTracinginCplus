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
            auto r = double(j) / (img_width-1);
            auto g = double(i) / (img_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999*r);
            int ig = static_cast<int>(255.999*g);
            int ib = static_cast<int>(255.999*b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}