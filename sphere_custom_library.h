#ifndef SPHERE_CUSTOM_LIBRARY_H
#define SPHERE_CUSTOM_LIBRARY_H

#include "hittable_custom_library.h"
#include "vector_custom_library.h"

class object_as_sphere : public hittable{
    public:
    object_as_sphere() {}
    object_as_sphere(const vector3& cer, double r):center(cer),radius(r){};
    vector3 center;
    double radius;
    virtual bool hit(const ray& r , double t_min,double t_max, hit_detail& data_record)const;
    };
    
    bool object_as_sphere::hit(const ray& r , double t_min,double t_max, hit_detail& data_record)const
    {

    vector3 oc = center - r.give_orig();
    auto a = dot(r.give_dir(), r.give_dir());
    auto b = -2.0 * dot(r.give_dir(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if(discriminant <0) {return false;}
    
    auto root_at_point= std::min((-b-sqrt(discriminant))/(2.0*a),(-b+sqrt(discriminant))/(2.0*a));
    if(root_at_point>t_max || root_at_point<t_min) return false;
    if(root_at_point<=t_max && root_at_point>=t_min)
    {
        data_record.t=root_at_point;
        data_record.point_of_intersection=r.at(root_at_point);
        data_record.normal_at_intersection=(data_record.point_of_intersection-center)/radius;
        data_record.set_face_normal(r, data_record.normal_at_intersection);
        return true;
    }
    }
#endif

// double hit_sphere(const ray& r , double radius, const vector3& center)
// {
//     vector3 oc = center - r.give_orig();
//     auto a = dot(r.give_dir(), r.give_dir());
//     auto b = -2.0 * dot(r.give_dir(), oc);
//     auto c = dot(oc, oc) - radius*radius;
//     auto discriminant = b*b - 4*a*c;
//     if(discriminant <0) {return -1.0;}
//     else 
//     {
//     return (-b-sqrt(discriminant))/(2.0*a);
//     }

// }

// double hit_ellipsoid(const vector3& center, const vector3& radius, const ray& r) {

//     //The ellipsoid equation is (x/a)^2 + (y/b)^2 + (z/c)^2 = 1, where a, b, and c are the radius w.r.t. x, y, and z axes
//     vector3 inv_radius(1.0 / radius.give_x() , 1.0 / radius.give_y(), 1.0 / radius.give_z()); 

//     vector3 scaled_origin = r.give_orig() * inv_radius;//transform the ray into the ellipsoid's local coordinate system.
//     vector3 scaled_direction = r.give_dir() * inv_radius;//the ray is aligned with the scaled coordinate system.

//     vector3 oc = r.give_orig() - center;//compute the intersection point by solving the quadratic equation

//     //r(t)= o+t⋅d
//     auto a = dot(scaled_direction, scaled_direction);//square of the ray’s direction magnitude
//     auto b = 2.0 * dot(scaled_direction, oc);//dot product of the direction and the vector from the ray origin to the ellipsoid’s center
//     auto c = dot(oc, oc) - 1.0;//squared distance from the ray origin to the ellipsoid's center minus the ellipsoid's radius 

//     auto discriminant = b * b - 4 * a * c;

//     if(discriminant <0) {return -1.0;}
//     else 
//     {
//     return (-b-sqrt(discriminant))/(2.0*a);
//     } // needed first root from the camera // shortest root path 
// }