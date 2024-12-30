#include "color_custom_library.h"
#include "ray_custom_library.h"
#include "vector_custom_library.h"
#include "hittable_list_custom_library.h"
#include "hittable_custom_library.h"
#include "sphere_custom_library.h"
#include "camera_custom_library.h"

#include <iostream>



int main() {
    hittable *list[3];
    list[0]=new object_as_sphere(vector3(0,0,-1),0.5);
    list[1]=new object_as_sphere(vector3(0,-100.5,-1),100);
    //list[2]=new object_as_sphere(vector3(0,100.5,-1),100);
    hittable* world=new hittable_list(list,2); //object creation 
    camera cam;
    cam.render(world);
}