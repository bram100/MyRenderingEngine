//
//  matrix.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/8/23.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <assert.h>

#include "ray.hpp"
#include "vector.hpp"
#include "localGeo.hpp"

class matrix4 {
    public:
    
    //constructors
    //identity
    matrix4() { m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
                m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2]
                = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0]
                = m[3][1] = m[3][2] = 0.f; }
    
    matrix4(float mat[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = mat[i][j];
        }
    }
}
    //wtf is this
    matrix4(const std::initializer_list<std::initializer_list<float>>& initList) {
        int i = 0;
        for (const auto& row : initList) {
            int j = 0;
            for (const auto& value : row) {
                m[i][j] = value;
                j++;
            }
            i++;
        }
    }


float* operator[](int row) {
    return m[row];
}

const float* operator[](int row) const {
    return m[row];
}

    matrix4(float t00, float t01, float t02, float t03,
            float t10, float t11, float t12, float t13,
            float t20, float t21, float t22, float t23,
            float t30, float t31, float t32, float t33) :  m{{t00, t01, t02, t03}, {t10, t11, t12, t13}, {t20, t21, t22, t23}, {t30, t31, t32, t33}} {}

    
    //Parameterized constructor
    //for transformation intialization
    matrix4(float t03, float t13, float t23) : matrix4() {
        this->m[0][3] = t03;
        this->m[1][3] = t13;
        this->m[2][3] = t23;
    }

    
    //getters/setters
    bool operator==(matrix4 &object) const {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    if (m[i][j] != object.m[i][j]) return false;
            return true;
        }
    
    
    
    matrix4& operator=(const matrix4& other) {
          for (int i = 0; i < 4; ++i) {
              for (int j = 0; j < 4; ++j) {
                  m[i][j] = other.m[i][j];
              }
          }
          return *this;
      }
    
    
    matrix4 operator*( const matrix4 &object)const {
        matrix4 result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result.m[i][j] = 0;
                    for (int k = 0; k < 4; k++) {
                        result.m[i][j] += m[i][k] * object.m[k][j];
                    }
                }
            }
            return result;
        }
    
    
    
    ray operator*(const ray& r) {
        
        ray transformedRay;
        vector4<float> holdLookAt;
        vector4<float> holdLookFrom;
        vector4<float> lookFrom4 = vector4<float>(r.lookFrom, 1.f);
        vector4<float> lookAt4 = vector4<float>(r.lookAt, 0.f);
        
        holdLookAt[0] = m[0][0] * lookAt4[0] + m[0][1] * lookAt4[1] + m[0][2] * lookAt4[2] + m[0][3] * lookAt4[3];
        holdLookAt[1] = m[1][0] * lookAt4[0] + m[1][1] * lookAt4[1] + m[1][2] * lookAt4[2] + m[1][3] * lookAt4[3];
        holdLookAt[2] = m[2][0] * lookAt4[0] + m[2][1] * lookAt4[1] + m[2][2] * lookAt4[2] + m[2][3] * lookAt4[3];
        holdLookAt[3] = m[3][0] * lookAt4[0] + m[3][1] * lookAt4[1] + m[3][2] * lookAt4[2] + m[3][3] * lookAt4[3];

        holdLookFrom[0] = m[0][0] * lookFrom4[0] + m[0][1] * lookFrom4[1] + m[0][2] * lookFrom4[2] + m[0][3] * lookFrom4[3];
        holdLookFrom[1] = m[1][0] * lookFrom4[0] + m[1][1] * lookFrom4[1] + m[1][2] * lookFrom4[2] + m[1][3] * lookFrom4[3];
        holdLookFrom[2] = m[2][0] * lookFrom4[0] + m[2][1] * lookFrom4[1] + m[2][2] * lookFrom4[2] + m[2][3] * lookFrom4[3];
        holdLookFrom[3] = m[3][0] * lookFrom4[0] + m[3][1] * lookFrom4[1] + m[3][2] * lookFrom4[2] + m[3][3] * lookFrom4[3];

        vector3<float> lookFrom3 = vector3<float>(holdLookFrom.xyz());
        vector3<float> lookAt3 = vector3<float>(holdLookAt.xyz());
        
        transformedRay.lookAt = lookAt3;
        transformedRay.lookFrom = lookFrom3;
        
        return transformedRay;
        
    }
    
    localGeo operator*(const localGeo currentLG) {
                
        localGeo transformedLG;
        
        transformedLG.pos.x = currentLG.pos.x * m[0][0] + currentLG.pos.y * m[1][0] + currentLG.pos.z * m[2][0];
        transformedLG.pos.y = currentLG.pos.x * m[0][0] + currentLG.pos.y * m[1][0] + currentLG.pos.z * m[2][0];
        transformedLG.pos.z = currentLG.pos.x * m[0][0] + currentLG.pos.y * m[1][0] + currentLG.pos.z * m[2][0];

        transformedLG.normal.x = currentLG.normal.x * m[0][0] + currentLG.normal.y * m[1][0] + currentLG.normal.z * m[2][0];
        transformedLG.normal.y = currentLG.normal.x * m[0][0] + currentLG.normal.y * m[1][0] + currentLG.normal.z * m[2][0];
        transformedLG.normal.z = currentLG.normal.x * m[0][0] + currentLG.normal.y * m[1][0] + currentLG.normal.z * m[2][0];
        
        return transformedLG;

    }

    //do I need this???
    vector4<float> operator*(const vector4<float>& vec) {
        
        vector4<float> transformedVec;
        
        transformedVec[0] = m[0][0] * vec[0] + m[0][1] * vec[1] + m[0][2] * vec[2] + m[0][3] * vec[3];
        transformedVec[1] = m[1][0] * vec[0] + m[1][1] * vec[1] + m[1][2] * vec[2] + m[1][3] * vec[3];
        transformedVec[2] = m[2][0] * vec[0] + m[2][1] * vec[1] + m[2][2] * vec[2] + m[2][3] * vec[3];
        transformedVec[3] = m[3][0] * vec[0] + m[3][1] * vec[1] + m[3][2] * vec[2] + m[3][3] * vec[3];


        return transformedVec;
    }
    
    point3<float> operator*(const point3<float>& vec) {
        
        point3<float> transformedVec;
        
        //4th value of point3 is 1.0f
        
        transformedVec[0] = m[0][0] * vec[0] + m[0][1] * vec[1] + m[0][2] * vec[2] + m[0][3] * 1.f;
        transformedVec[1] = m[1][0] * vec[0] + m[1][1] * vec[1] + m[1][2] * vec[2] + m[1][3] * 1.f;
        transformedVec[2] = m[2][0] * vec[0] + m[2][1] * vec[1] + m[2][2] * vec[2] + m[2][3] * 1.f;
        transformedVec[3] = m[3][0] * vec[0] + m[3][1] * vec[1] + m[3][2] * vec[2] + m[3][3] * 1.f;


        return transformedVec;
    }
    
    vector3<float> operator*(const vector3<float>& v) {
        vector3<float> transformedVec;
        //v.w = 0;

        transformedVec.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
        transformedVec.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
        transformedVec.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];

        return transformedVec;
    }
    
    friend vector3<float> operator*(const vector3<float>& v, const matrix4& m) {
        vector3<float> transformedVec;
        //v.w = 0;
        
        transformedVec.x = v.x * m[0][0] + v.y * m[1][0] +
                   v.z * m[2][0] + 0 * m[3][0];

        transformedVec.y = v.x * m[0][1] + v.y * m[1][1] +
                   v.z * m[2][1] + 0 * m[3][1];

        transformedVec.z = v.x * m[0][2] + v.y * m[1][2] +
                   v.z * m[2][2] + 0 * m[3][2];

        return transformedVec;
    }

    float m[4][4];
};

#endif /* matrix_hpp */
