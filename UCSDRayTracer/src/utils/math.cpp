//
//  math.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/20/23.
//

#include "math.hpp"
#include <math.h>  
#include <iostream>
#include "matrix.hpp"

class math math;
bool math::solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
    float discr = (b * b) - (4 * a * c);
    
    if (discr < 0) {

        return false;
    }
    else if (discr == 0) {
        
        x0 = x1 = - 0.5 * b / a;
    }

    else {
        
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;

    }

    if (x0 > x1) std::swap(x0, x1);

    return true;
    
}

float math::Radians(float deg) {
    return (pi / 180) * deg;
}





float MathOperations::cosineAngle(const vector3<float>& a, const vector3<float>& b) {
    float dotProduct = a * b; //dot product
    float magnitudeA = a.Length(); //Magnitude(a);
    float magnitudeB = b.Length(); //Magnitude(b);
    
    // Make sure the magnitudes are not zero
    if (magnitudeA == 0.0f || magnitudeB == 0.0f) {
        return 0.0f; // Angle doesn't make sense, return 0
    }
    
    return dotProduct / (magnitudeA * magnitudeB);
}
