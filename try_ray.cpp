#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"
#include "hittable_list_custom_library.h"
#include "hittable_custom_library.h"
#include "sphere_custom_library.h"
#include "camera_custom_library.h"
#include "material_custom_library.h"
#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include<sstream>


hittable *scene(){
int num=100;
hittable **list=new hittable*[num+1];
list[0] = new object_as_sphere(vector3(0,-1000,0),1000,new lambertian(vector3(0.5,0.5,0.5)));
	int i = 1;
	for(int a=-5;a<5;a++) {
		for(int b=-5;b<5;b++) {
			double choose_mat = random_double();
			vector3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
			if(choose_mat < 0.8) {
				list[i++] = new object_as_sphere(center, 0.2, new lambertian(vector3(random_double()*random_double(),random_double()*random_double(),random_double()*random_double())));
			} else if(choose_mat < 0.95) {
				list[i++] = new object_as_sphere(center, 0.2, new metal(vector3(0.5*(1+random_double()),0.5*(1+random_double()),0.5*(1+random_double())),0.5*random_double()));
			} else {
				list[i++] = new object_as_sphere(center, 0.2, new dielectric(1.5));
			}
			
		}
	}
	list[i++] = new object_as_sphere(vector3(0,1,0), 1, new dielectric(1.5));
	list[i++] = new object_as_sphere(vector3(-4,1,0), 1, new lambertian(vector3(.4,.2,.1)));
	list[i++] = new object_as_sphere(vector3(4,1,0), 1, new metal(vector3(.7,.6,.5),0));
	return new hittable_list(list,i);
//return new hittable_list(list,num);
}

hittable *world=scene();
int sample_pixel=100;
int image_width=400;
int image_height=200;
double dist_to_focus = 10.0;
double aperture = 0.1;
vector3 lookfrom(13,3,2);
vector3 lookat(0,0,0);
camera cam(lookfrom,lookat,vector3(0,1,0),20, double(image_width)/double(image_height),aperture,dist_to_focus);
//cam.render(world,image_width,image_height,sample_pixel);
    

// static void fast_trace(int i ,int j)
// {
//     //std::cout<< "P3\n" << image_width << " " << image_height << "\n255\n";
//             vector3 col(0,0,0);
//             for(int k=0;k<sample_pixel;k++)
//             {
//             double delta_u=double(i+random_double())/image_width;
//             double delta_v=double(j+random_double())/image_height;
//             ray temp=cam.get_ray(delta_u,delta_v);
//             //vector3 point=temp.at(2.0);
//             col+=cam.ray_color(temp,world,0);
//             }
//             col/=double(sample_pixel);
//             //do_color(std::cout,col);
//             col = vector3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
// 			int ir = int(255.99*col[0]);
// 			int ig = int(255.99*col[1]);
// 			int ib = int(255.99*col[2]);
// 			//if(x % image_width == 1) sdltemplate::loop(); 
// 			std::cout << ir << " " << ig << " " << ib << "\n";
        
// }

void flipImage(std::vector<std::string>& pixel_data, int image_width, int image_height) {
    for (int y = 0; y < image_height / 2; ++y) {
        for (int x = 0; x < image_width; ++x) {
            std::swap(pixel_data[y * image_width + x], pixel_data[(image_height - 1 - y) * image_width + x]);
        }
    }
}
int main() {
	auto start = std::chrono::high_resolution_clock::now();
    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    // for(int y=image_height-1; y>=0; y--) {
	// 	for(int x=0; x<image_width; x++) {
	// 		std::async(std::launch::async,fast_trace,x,y);
	// 	}
	// }
    
       std::ofstream image("output_final_12.ppm");
        if (!image) {
            std::cerr << "Error: Could not open the file for writing." << std::endl;
            exit(1);
        }

        image << "P3\n" << image_width << " " << image_height << "\n255\n";

        // Vector to store the final color data for all pixels
        std::vector<std::string> pixel_data(image_width * image_height);

        // Vector to store futures
        std::vector<std::future<void>> futures;

        // Launch tasks asynchronously
        for (int j=image_height-1;j>=0 ;--j) {
            for (int i =0;i<image_width ;++i) {
                futures.emplace_back(std::async(std::launch::async,[&, i, j]() {
                        // Compute the color for the pixel
                        vector3 col(0,0,0);
                        for (int sample = 0; sample < sample_pixel ; ++sample) {
							double delta_u=double(i+random_double())/image_width;
            				double delta_v=double(j+random_double())/image_height;
                            ray r = cam.get_ray(delta_u, delta_v);
                            col += cam.ray_color(r,world,0);
                        }
						col/=double(sample_pixel);
                        col= vector3(sqrt(col.r()),sqrt(col.g()),sqrt(col.b()));
						int ir = int(255.99*col[0]);
						int ig = int(255.99*col[1]);
						int ib = int(255.99*col[2]);
						pixel_data[j * image_width + i] = std::to_string(ir) + " " +
                                              std::to_string(ig) + " " +
                                              std::to_string(ib) + "\n";
                    }
                ));
            }
        }

        // Wait for all tasks to complete
        for (auto& fut : futures) {
            fut.get();
        }
		flipImage(pixel_data, image_width, image_height);
        // Write the collected data to the file
        for (const auto& row : pixel_data) {
            image << row;
        }
		
        image.close();
        std::cout << "Image generated successfully in output.ppm" << std::endl;
		std::clog << "\rDone.\n";
		auto end = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double> elapsed = end - start;
    	std::cout<<"Time taken to render the image: "<<elapsed.count()<<" seconds";
}