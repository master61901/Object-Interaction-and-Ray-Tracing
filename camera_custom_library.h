#ifndef CAMERA_CUSTOM_LIBRARY_H
#define CAMERA_CUSTOM_LIBRARY_H

#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"
#include "hittable_list_custom_library.h"
#include "hittable_custom_library.h"
#include "sphere_custom_library.h"
#include "material_custom_library.h"
#include <cfloat>
#include <iostream>
#include <random>

vector3 random_in_unit_disk() {
	vector3 p;
	do {
		p = 2.0*vector3(random_double(),random_double(),0.0) - vector3(1,1,0);
	} while(dot(p,p)>=1.0);
	return p;
}
class camera 
{
    public:
    camera(vector3 lookfrom, vector3 lookat, vector3 vup, double vfov, double aspect, double aperture, double focus_dist) {
 	lens_radius = aperture / 2;
 	double theta = vfov*M_PI/180;
 	double half_height = tan(theta/2);
 	double half_width = aspect * half_height;
 	origin = lookfrom;
 	w = unit_vector(lookfrom - lookat);
 	u = unit_vector(cross(vup,w));
 	v = cross(w,u);
 	lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
	horizontal=2*half_width*u*focus_dist;
	vertical=2*half_height*v*focus_dist;
    }
	
	ray get_ray(double s, double t) {
 	vector3 rd = lens_radius*random_in_unit_disk();
 	vector3 offset = u * rd.give_x() + v * rd.give_y();
 	return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
 }

	// void render(hittable *world,int image_width,int image_height,int sample_pixel)
    // {
    //     std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";
    // for (int j = image_height-1; j >=0; j--) {
    //     std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    //     for (int i = 0; i < image_width; i++) {
    //         vector3 col(0,0,0);
    //         for(int k=0;k<sample_pixel;k++)
    //         {
    //         double delta_u=double(i+random_double())/image_width;
    //         double delta_v=double(j+random_double())/image_height;
    //         ray temp=get_ray(delta_u,delta_v);
    //         //vector3 point=temp.at(2.0);
    //         col+=ray_color(temp,world,0);
    //         }
    //         col/=double(sample_pixel);
    //         do_color(std::cout,col);
    //     }
    // // }
    //     std::clog << "\rDone.\n";
    // }

    vector3 ray_color(const ray& r,hittable *world,int depth){
    hit_detail rec;
    if(world->hit(r,0.001,DBL_MAX,rec))
    {
        //if(depth<0) return color(0,0,0);
        /*vector3 direction = random_on_hemisphere(rec.normal_at_intersection);
        return std::sqrt(1.0) * ray_color(ray(rec.point_of_intersection, direction), world);*/
        ray scattered;
        vector3 attenuation;
        if(depth<8 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
        {
            return attenuation*ray_color(scattered,world,depth+1);
        }
        else {return color(0,0,0);} 
    }else {
    // auto root=hit_sphere(vector3(0,0,-1),0.5,r);
    // if(root>0.0)
    // {
    // vector3 unit_vector_at_point=unit_vector(r.at(root)-vector3(0,0,-1));
    // return 0.5*vector3(unit_vector_at_point.give_x()+1, unit_vector_at_point.give_y()+1,unit_vector_at_point.give_z()+1);
    // }


    vector3 unit_direction = unit_vector(r.give_dir()); // unit vector of magnitude one
    auto a = 0.5*(unit_direction.give_y() + 1.0); // to scale the value of a based on y from 0 to 1
    return (1.0-a)*vector3(1.0, 1.0, 1.0) + a*vector3(0.5, 0.7, 1.0); // color of white  // color of blue
}
    }

    vector3 lower_left_corner,horizontal,vertical,origin;
    double lens_radius;
    vector3 u,v,w;
};

#endif