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



extern math math;

#endif /* math_hpp */

