//
//  math.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/20/23.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <cmath>
#include "point.hpp"
#include "vector.hpp"

const double pi = std::acos(-1);
const float kEpsilon = 1e-6f; //almost zero 

class math {
public:
    bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);

    
    
    static float Radians(float deg);
    
    

};


namespace MathOperations {
template <typename T, typename U>
    float dotProduct(const T& a, const U& b) {
        return a.x * b.x + b.y * b.y + a.z * b.z;
    }
}
typedef normal<float> normalf; //are these neeeded?
typedef vector3<float> vector3f; //are these neeeded?



extern math math;

#endif /* math_hpp */

