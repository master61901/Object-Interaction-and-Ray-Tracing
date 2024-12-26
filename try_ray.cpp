#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"

#include <iostream>
#include <bits/stdc++.h>


vector3 ray_color(const ray& r) {
   vector3 unit_direction = unit_vector(r.give_dir()); // unit vector of magnitude one
   //std::clog<<r.give_dir();
    auto a = 0.5*(unit_direction.give_y() + 1.0); // to scale the value of a based on y from 0 to 1
    return (1.0-a)*vector3(1.0, 1.0, 1.0) + a*vector3(0.5, 0.7, 1.0); // color of white  // color of blue
}

int main() {
    int image_width=400;
    int image_height=200;
    
    vector3 camera_center=vector3(0.0,0.0,0.0);
    vector3 horizontal_grid=vector3(4.0,0.0,0.0);
    vector3 vertical_grid=vector3(0.0,2.0,0.0);
    auto user_input=vector3(-2.0,-1.0,-1.0);

    std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >=0; j--) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            double delta_u=double(i)/image_width;
            double delta_v=double(j)/image_height;
            ray r(camera_center,user_input+delta_u*horizontal_grid+delta_v*vertical_grid);
            vector3 pixel = ray_color(r);
            do_color(std::cout, pixel);
        }
    }
                  

    std::clog << "\rDone.\n";
}