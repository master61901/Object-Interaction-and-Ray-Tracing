#ifndef RAY_CUSTOM_LIBRARY_H
#define RAY_CUSTOM_LIBRARY_H

#include "vector_custom_library.h"
#include <iostream>

class ray {
  public:
    ray(){}   //Default constructor 
    

    ray(const vector3& origin, const vector3& direction) { this->orig=origin;this->dir=direction; }

    //first put external parameters to orig and dir containers and then do calculation 
    //members in private can only be accessed by the same class
    
    const vector3 &give_dir() const {return dir;}
    const vector3 &give_orig() const {return orig;}
    vector3 at(double t) const {
        return orig + t*dir; //mx+c
    }

  private:
    vector3 orig;
    vector3 dir;
};

#endif
