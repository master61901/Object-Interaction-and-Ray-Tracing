#include "color_custom_library.h"
#include "vector_custom_library.h"

#include <iostream>

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            do_color(std::cout, pixel);
        }
    }

    std::clog << "\rDone\n";
}