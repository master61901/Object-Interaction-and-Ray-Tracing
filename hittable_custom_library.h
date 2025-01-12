#ifndef HITTABLE_CUSTOM_LIBRARY_H
#define HITTABLE_CUSTOM_LIBRARY_H

#include "ray_custom_library.h"
#include "vector_custom_library.h"

class material; 

class hit_detail{ // to hold the details for ray intersection with the object 
    public:
    vector3 point_of_intersection;
    double t;
    vector3 normal_at_intersection;
    //bool front_face;
    material* mat_ptr;

    // void set_face_normal(const ray& r, const vector3& outward_normal)  // normal aganist the ray direction always helps in refraction concept
    // {
    //     front_face = dot(r.give_dir(), outward_normal) < 0;
    //     normal_at_intersection = front_face ? outward_normal : -outward_normal;
    // }
};

class hittable{  //abstarct class -that cannot be instantiated on its own and is designed to serve as a base class for other classes. It typically 
//includes at least one pure virtual function
// we are adding all the objects into an big vessel i.e abstract class 
// with a fucntion called hit() 
public:
virtual bool hit(const ray& r , double t_min,double t_max, hit_detail& data_record) const =0;

};

#endif
