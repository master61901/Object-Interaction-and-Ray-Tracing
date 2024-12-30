#ifndef VECTOR_CUSTOM_LIBRARY_H
#define VECTOR_CUSTOM_LIBRARY_H

#include <cmath>
#include <random>
#include <iostream>

class vector3
{
public:
double main_vector[3];//to hold x,y,z
vector3() : main_vector{0,0,0} {}
vector3(double x, double y, double z) : main_vector{x,y,z} {}
double give_x()const {return main_vector[0];}//return x value
double give_y()const {return main_vector[1];}
double give_z()const {return main_vector[2];}
vector3 operator-()const {return vector3{-main_vector[0],-main_vector[1],-main_vector[2]};}
double operator[](int index)const {return main_vector[index];}
double& operator[](int index){return main_vector[index];}
vector3& operator+=(const vector3& v)
{
    main_vector[0]+=v.main_vector[0];
    main_vector[1]+=v.main_vector[1];
    main_vector[2]+=v.main_vector[2];
    return *this;
}
vector3& operator*=(double t)
{
    main_vector[0]*=t;
    main_vector[1]*=t;
    main_vector[2]*=t;
    return *this;
}
vector3& operator/=(double t) 
{
        return *this *= 1/t;
}
double length_squared() const 
{
        return main_vector[0]*main_vector[0] + main_vector[1]*main_vector[1] + main_vector[2]*main_vector[2];
}
double length() const 
{
        return std::sqrt(length_squared());
}
};  
inline std::ostream& operator<<(std::ostream& out, const vector3& v) {
    return out << v.main_vector[0] << ' ' << v.main_vector[1] << ' ' << v.main_vector[2];
}

inline vector3 operator+(const vector3& u, const vector3& v) {
    return vector3(u.main_vector[0] + v.main_vector[0], u.main_vector[1] + v.main_vector[1], u.main_vector[2] + v.main_vector[2]);
}

inline vector3 operator-(const vector3& u, const vector3& v) {
    return vector3(u.main_vector[0] - v.main_vector[0], u.main_vector[1] - v.main_vector[1], u.main_vector[2] - v.main_vector[2]);
}

inline vector3 operator*(const vector3& u, const vector3& v) {
    return vector3(u.main_vector[0] * v.main_vector[0], u.main_vector[1] * v.main_vector[1], u.main_vector[2] * v.main_vector[2]);
}

inline vector3 operator*(double t, const vector3& v) {
    return vector3(t*v.main_vector[0], t*v.main_vector[1], t*v.main_vector[2]);
}

inline vector3 operator*(const vector3& v, double t) {
    return t * v;
}

inline vector3 operator/(const vector3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vector3& u, const vector3& v) {
    return u.main_vector[0] * v.main_vector[0]
         + u.main_vector[1] * v.main_vector[1]
         + u.main_vector[2] * v.main_vector[2];
}

inline vector3 cross(const vector3& u, const vector3& v) {
    return vector3(u.main_vector[1] * v.main_vector[2] - u.main_vector[2] * v.main_vector[1],
                u.main_vector[2] * v.main_vector[0] - u.main_vector[0] * v.main_vector[2],
                u.main_vector[0] * v.main_vector[1] - u.main_vector[1] * v.main_vector[0]);
}

inline vector3 unit_vector(const vector3& v) {
    return v / v.length();
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min,double max) {
    static std::uniform_real_distribution<double> distribution(min,max);
    static std::mt19937 generator;
    return distribution(generator);
}
inline vector3 random_gen(double min, double max) {
        return vector3(random_double(min,max), random_double(min,max), random_double(min,max));
}

inline vector3 random_unit_vector() {
    while (true) {
        auto p = random_gen(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}


inline vector3 random_on_hemisphere(const vector3& normal) {
    vector3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif



