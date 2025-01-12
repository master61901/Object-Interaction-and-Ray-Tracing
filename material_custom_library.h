#ifndef MATERIAL_CUSTOM_LIBRARY_H
#define MATERIAL_CUSTOM_LIBRARY_H

#include "hittable_custom_library.h"

class material {
  public:
    virtual bool scatter(const ray& r_in,const hit_detail&  record,vector3& attenuation,ray& scattered) const=0;
};

class lambertian : public material{
    public:
    lambertian(const vector3& a) :albedo(a) {}
    virtual bool scatter(const ray& r_in,const hit_detail& record, vector3& attenuation,ray& scattered) const {
        vector3 target=record.point_of_intersection+record.normal_at_intersection+random_in_unit_sphere();
        scattered=ray(record.point_of_intersection,target-record.point_of_intersection);
        attenuation=albedo;
        return true;
    }
    color albedo;
};

class metal : public material {
    public:
    metal(const vector3& a,double f): albedo(a){if(f<1) fuzz=f; else fuzz=1;}//albedo is the color of the object
    virtual bool scatter(const ray& r_in,const hit_detail& record, vector3& attenuation, ray& scattered) const {
        vector3 reflected = reflect(unit_vector(r_in.give_dir()),record.normal_at_intersection);
        scattered = ray(record.point_of_intersection, reflected +fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.give_dir(),record.normal_at_intersection) > 0);
    }
    color albedo;
    int fuzz;
    //double fuzz;
};

class dielectric : public material {
public:
 dielectric(double ri) : ref_idx(ri) {}
 virtual bool scatter(const ray& r_in, const hit_detail& rec, vector3& attenuation, ray& scattered) const {
 	vector3 outward_normal;
 	vector3 reflected = reflect(r_in.give_dir(), rec.normal_at_intersection);
 	double ni_over_nt;
 	attenuation = vector3(1.0,1.0,1.0);
 	vector3 refracted;
 	double reflect_prob;
 	double cosine;
 	if(dot(r_in.give_dir(), rec.normal_at_intersection) > 0) {
 		outward_normal = -rec.normal_at_intersection;
 		ni_over_nt = ref_idx;
 		cosine = dot(r_in.give_dir(), rec.normal_at_intersection) / r_in.give_dir().length();
 		cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
 	} else {
 		outward_normal = rec.normal_at_intersection;
 		ni_over_nt = 1.0 / ref_idx;
 		cosine = -dot(r_in.give_dir(),rec.normal_at_intersection) / r_in.give_dir().length();
 	}
 	if(refract(r_in.give_dir(), outward_normal, ni_over_nt, refracted)) {
 		reflect_prob = schlick(cosine,ref_idx);
 	} else {
 		reflect_prob = 1.0;
 	}
 	if (random_double() < reflect_prob) {
 		scattered = ray(rec.point_of_intersection,reflected);
 	} else {
 		scattered = ray(rec.point_of_intersection,refracted);
 	}
 	return true;
 }
 double ref_idx;
};



#endif