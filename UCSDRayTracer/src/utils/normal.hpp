//
//  normal.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/8/23.
//

#ifndef normal_hpp
#define normal_hpp


#include <stdio.h>
#include <cassert>
#include <iostream>
#include <cmath>

#include "vector.hpp"

template <typename T>
class normal {

    public:
        
        normal() {x = y = z = 0; }
    
        normal(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {  }

        //getters/setters
    
        normal(const normal<T> &object) {
            x = object.x;
            y = object.y;
            z = object.z;
        };
    

    
        
        normal<T>& operator=(const normal<T> &object) {
            x = object.x;
            y = object.y;
            z = object.z;
        
            return *this;
        };
         
    
        T operator[](unsigned int index) const {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x;
            if (index == 1) return y;
            return z;
        };
        
        T &operator[](unsigned int index) {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x;
            if (index == 1) return y;
            return z;
        };
    

    
        //opperators (overloading)
    
        normal<T> operator+(const normal<T> &object) const {
            return normalize(vector3(x + object.x, y + object.y, z + object.z));
        };
    

        normal<T> operator-(const normal<T> &object) const {
            return normalize(vector3(x - object.x, y - object.y, z - object.z));
        };
    
        friend normal operator*(float scalar, const normal& norm) {
            return normal(scalar * norm.x, scalar * norm.y, scalar * norm.z);
        }

    
    template <typename U>
        normal<T>& operator=(const vector3<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
            
            return *this;
        }

    normal<T> operator/(T scalar) const {
        T invLength = T(1) / scalar;
        return normal<T>(x * invLength, y * invLength, z * invLength);
    }

    
          
    float Length() const { return std::sqrt(x * x + y * y + z * z); }
    
    T x, y, z;
    

};
typedef normal<float> normalf; //are these neeeded?
//typedef normal<int> normali;

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const normal<T> &object) {
    os << "[ " << object.x << ", " << object.y  << ", " << object.z << " ]";
    return os;
}

//why is this out of scope of the class?
template <typename T>
inline normal<T> normalize(const normal<T> &v) {
    
    return v / v.Length();
   
}



#include <stdio.h>

#endif /* normal_hpp */
