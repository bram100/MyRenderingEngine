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
#include "matrix.hpp"

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
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename V, typename M>
//float is 0 or 1 for when v is length 3
    V matrixVector(const M& m, const V& v, const float f) {
        
        V transformedV;
        
        transformedV.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * f;
        transformedV.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * f;
        transformedV.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * f;
       // transformedV.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

        return transformedV;

    }

template <typename V, typename M>
//float is 0 or 1 for when v is length 3
    V vectorMatrix(const V& v, const M& m, const float f) {
        
        V transformedV;
        
        transformedV.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + f * m.m[3][0];
        transformedV.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + f * m.m[3][1];
        transformedV.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + f * m.m[3][2];
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return transformedV;

    }

template <typename V>
//float is 0 or 1 for when v is length 3
    V floatVector3(const float f, const V& v) {
        
        V resultV;
        
        resultV.x = f * v.x;
        resultV.y = f * v.y;
        resultV.z = f * v.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }

template <typename V>
//float is 0 or 1 for when v is length 3
    V floatVector3Add(const float f, const V& v) {
        
        V resultV;
        
        resultV.x = f + v.x;
        resultV.y = f + v.y;
        resultV.z = f + v.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }

template <typename V>
//float is 0 or 1 for when v is length 3
    V floatVector3Multiply(const float f, const V& v) {
        
        V resultV;
        
        resultV.x = f * v.x;
        resultV.y = f * v.y;
        resultV.z = f * v.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }

template <typename V>
//float is 0 or 1 for when v is length 3
    V vectorFloatSub(const V& v, const float f) {
        
        V resultV;
        
        resultV.x = v.x - f;
        resultV.y = v.y - f;
        resultV.z = v.z - f;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }


template <typename V, typename N>
//float is 0 or 1 for when v is length 3
    V vectorVectorAdd(const V& v, const N& n) {
        
        V resultV;
        
        resultV.x = v.x + n.x;
        resultV.y = v.y + n.y;
        resultV.z = v.z + n.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }


template <typename V, typename N>
//float is 0 or 1 for when v is length 3
    V vectorVectorSub(const V& v, const N& n) {
        
        V resultV;
        
        resultV.x = v.x - n.x;
        resultV.y = v.y - n.y;
        resultV.z = v.z - n.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }



template <typename V, typename N>
//float is 0 or 1 for when v is length 3
    V vectorVectorMultiply(const V& v, const N& n) {
        
        V resultV;
        
        resultV.x = v.x * n.x;
        resultV.y = v.y * n.y;
        resultV.z = v.z * n.z;
       // transformedV.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

        return resultV;

    }

float cosineAngle(const vector3<float>& a, const vector3<float>& b);
/*
float cosineAngle(const vector3<float>& a, const vector3<float>& b) {
    float dotProduct = a * b; //dot product
    float magnitudeA = a.Length(); //Magnitude(a);
    float magnitudeB = b.Length(); //Magnitude(b);
    
    // Make sure the magnitudes are not zero
    if (magnitudeA == 0.0f || magnitudeB == 0.0f) {
        return 0.0f; // Angle doesn't make sense, return 0
    }
    
    return dotProduct / (magnitudeA * magnitudeB);
}
*/
    
}



template <typename T, typename L>
float dot(const T &v1, const L &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T, typename L>
vector3<float> cross(const T &v1, const L &v2) {
    vector3<float> result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}





//typedef normal<float> normalf; //are these neeeded?
//typedef vector3<float> vector3f; //are these neeeded?



extern math math;

#endif /* math_hpp */

