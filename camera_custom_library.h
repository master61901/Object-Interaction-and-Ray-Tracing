#ifndef CAMERA_CUSTOM_LIBRARY_H
#define CAMERA_CUSTOM_LIBRARY_H

#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"
#include "hittable_list_custom_library.h"
#include "hittable_custom_library.h"
#include "sphere_custom_library.h"
#include <cfloat>
#include <iostream>
#include <random>

class camera 
{
    public:
    void render(hittable *world)
    {
    int sample_pixel=100;
    int image_width=400;
    int image_height=200;
    std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >=0; j--) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            vector3 col(0,0,0);
            for(int k=0;k<sample_pixel;k++)
            {
            double delta_u=double(i+random_double())/image_width;
            double delta_v=double(j+random_double())/image_height;
            ray temp=get_ray(delta_u,delta_v);
            vector3 point=temp.at(2.0);
            col+=ray_color(temp,world);
            }
            col/=double(sample_pixel);
            do_color(std::cout,col);
        }
    }
        std::clog << "\rDone.\n";
    }


    ray get_ray(double i, double j)
    {
    vector3 camera_center=vector3(0.0,0.0,0.0);
    vector3 horizontal_grid=vector3(4.0,0.0,0.0);//horizontal vector from one corner of the viewport based on aspect ratio of the image 
    vector3 vertical_grid=vector3(0.0,2.0,0.0);// vertical vector from one corner of the viewport based on aspect ratio of the image 
    auto user_input=vector3(-2.0,-1.0,-1.0);
    return ray(camera_center,user_input+i*horizontal_grid+j*vertical_grid-camera_center);
    }
    

    private:
    vector3 ray_color(const ray& r,hittable *world) {
    hit_detail rec;
    if(world->hit(r,0.001,DBL_MAX,rec))
    {
        vector3 direction = random_on_hemisphere(rec.normal_at_intersection);
        return std::sqrt(1.0) * ray_color(ray(rec.point_of_intersection, direction), world);
    }
    else 
    {
    // auto root=hit_sphere(vector3(0,0,-1),0.5,r);
    // if(root>0.0)
    // {
    // vector3 unit_vector_at_point=unit_vector(r.at(root)-vector3(0,0,-1));
    // return 0.5*vector3(unit_vector_at_point.give_x()+1, unit_vector_at_point.give_y()+1,unit_vector_at_point.give_z()+1);
    // }


    vector3 unit_direction = unit_vector(r.give_dir()); // unit vector of magnitude one
    auto a = 0.5*(unit_direction.give_y() + 1.0); // to scale the value of a based on y from 0 to 1
    return (1.0-a)*vector3(1.0, 1.0, 1.0) + a*vector3(0.0, 0.5, 0.0); // color of white  // color of blue
}
}

};

#endif