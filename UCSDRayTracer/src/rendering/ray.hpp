//
//  ray.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/8/23.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <cmath>

#include "point.hpp"
#include "vector.hpp"
//#include "transform.hpp"

//value of 1 for the origin and 0 for the direction for 4d vector/ray transformation

static const float infinity = std::numeric_limits<float>::infinity();



class ray {

    public:
    //posiiton = lookFrom
    //direction = lookAt
    
    ray() : lookFrom(0.f,0.f,0.f), lookAt(0,0,0), t_max(0), t_min(0) {}
    

    ray(const vector3<float> lookFrom, const vector3<float> lookAt, float t_max = infinity, float t_min = infinity * -1)
            : lookFrom(lookFrom), lookAt(lookAt), t_max(t_max), t_min(t_min) {}
    
    // Point pos
    vector3<float> lookFrom;
    
    // Vector dir
    vector3<float> lookAt;
    
    // float t_min, t_max
    float t_min;
    float t_max;
    
    ray(const ray &object) {
        lookFrom = object.lookFrom;
        lookAt = object.lookAt;
        t_max = object.t_max;
        t_min = object.t_min;
    };
    

    
    point3<float> pointAt(float t) const {
            return lookFrom + (lookAt * t);
        }

    point3<float> operator()(int t) const {
        return lookFrom + lookAt * t;
        
    }
    
    /*
    ray multRay(const transformation* transform) const {
        vector3<float> newLookFrom = transform->multPoint(lookFrom);
        vector3<float> newLookAt = transform->multVector(lookAt);
        return ray(newLookFrom, newLookAt);
    }
     */


};

template <typename T>
inline vector4<T> normalize(const vector4<T> &v) {
    return v / v.Length();
}


#endif /* ray_hpp */
