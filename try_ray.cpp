#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"
#include "hittable_list_custom_library.h"
#include "hittable_custom_library.h"
#include "sphere_custom_library.h"
#include "camera_custom_library.h"
#include "material_custom_library.h"

#include <iostream>
#include <future>
#include  <thread>

hittable *scene(){
hittable **l=new hittable*[4];
l[0]=new object_as_sphere(vector3(0,0,-1),0.5,new lambertian(vector3(0.8,0.3,0.3)));
l[1]=new object_as_sphere(vector3(0,-100.5,-1),100,new lambertian(vector3(0.8,0.8,0.8)));
l[2]=new object_as_sphere(vector3(1,0,-1),0.5,new metal(vector3(0.8,0.6,0.2),0));
l[3]=new object_as_sphere(vector3(-1,0,-1),0.5,new dielectric(0.5));
return new hittable_list(l,4);
}

hittable *world=scene();
int sample_pixel=100;
int image_width=400;
int image_height=200;
double dist_to_focus = 10.0;
double aperture = 0.1;
vector3 lookfrom(0,0,6);
vector3 lookat(0,0,0);
camera cam(lookfrom,lookat,vector3(0,1,0),20, double(image_width)/double(image_height),aperture,dist_to_focus);
//cam.render(world,image_width,image_height,sample_pixel);
    

static void fast_trace(int i ,int j)
{
    //std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";
            vector3 col(0,0,0);
            for(int k=0;k<sample_pixel;k++)
            {
            double delta_u=double(i+random_double())/image_width;
            double delta_v=double(j+random_double())/image_height;
            ray temp=cam.get_ray(delta_u,delta_v);
            //vector3 point=temp.at(2.0);
            col+=cam.ray_color(temp,world,0);
            }
            col/=double(sample_pixel);
            //do_color(std::cout,col);
            col = vector3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			//if(x % image_width == 1) sdltemplate::loop(); 
			std::cout << ir << " " << ig << " " << ib << "\n";
        
}


int main() {
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int y=image_height-1; y>=0; y--) {
		for(int x=0; x<image_width; x++) {
			std::async(std::launch::async,fast_trace,x,y);
		}
	}
    std::clog << "\rDone.\n";
}