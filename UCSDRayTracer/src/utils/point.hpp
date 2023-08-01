//
//  point.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/8/23.
//


#ifndef point_hpp
#define point_hpp

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <cmath>
//#include "matrix.hpp"
//#include "vector.hpp"

template <typename T>
class vector3;
class matrix4;

template <typename T>
class point3 {

    public:
        
    
        point3() {x = y = z = 0; }
    
        point3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {  }

        // Constructor with one argument
        point3(T value) : x(value), y(value), z(value) {}

        //getters/setters
    
        point3(const point3<T> &object) {
            x = object.x;
            y = object.y;
            z = object.z;
        };
    
    
    point3<T>& operator=(const point3<T>& object) {
        if (this == &object)
            return *this;
        x = object.x;
        y = object.y;
        z = object.z;
        return *this;
    }

    
  
         
    
        T operator[](unsigned int index) const {
            if (index >= 0 && index <= 2) {
                if (index == 0) return x;
                if (index == 1) return y;
                return z;
            }
            //to allow for multiplcation by a tranformation matrix
            else if (index == 3 ) {
                static T one = T(1);
                return one;
            }
            else {
                std::cerr << "Error: index out of rancge " << std::endl;
            }
        };
        
        T &operator[](unsigned int index) {
            if (index >= 0 && index <= 2) {
                if (index == 0) return x;
                if (index == 1) return y;
                return z;
            }
            //to allow for multiplcation by a tranformation matrix
            else if (index == 3 ) {
                static T one = T(1);
                return one;
            }
            else {
                std::cerr << "Error: index out of rancge " << std::endl;
            }
        };
    
        //opperators (overloading)
    
        point3<T> operator+(const point3<T> &object) const {
            return point3(x + object.x, y + object.y, z + object.z);
        };
/*
        point3<T> operator-(const point3<T> &object) const {
            return point3(x - object.x, y - object.y, z - object.z);
        };
    */
        vector3<T> operator-(const point3<T>& other) const {
            return vector3<T>(x - other.x, y - other.y, z - other.z);
        }
    
    
    operator point3<T>() const {
        return point3<T>(x, y, z);
    }

/*
    template <typename U>
        point3<T> operator*(U scalar) const {
            return point3<T>(scalar * x, scalar * y, scalar * z);
        };
*/
    /*
    
    //cross product
    point3<T> operator^(const point3<T>& object) const {
        float crossX = y * object.z - z * object.y;
        float crossY = z * object.x - x * object.z;
        float crossZ = x * object.y - y * object.x;
        return point3<T>(crossX, crossY, crossZ);
    }
    
    //dot product //change int to T eventually
    template<typename U>
    int operator*(const point3<U>& other) const {
      return x * other.x + y * other.y + z * other.z;
    }

    */

    
    
    
    T operator*(const point3<T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    //Euclidean distance
    float Length() const { return std::sqrt(x * x + y * y + z * z); }
    
    T x, y, z;
    
    //template <typename X>


};

typedef point3<float> point3f; //are these neeeded?
typedef point3<int> point3i;

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const point3<T> &object) {
    os << "[ " << object.x << ", " << object.y  << ", " << object.z << " ]";
    return os;
}

//why is this out of scope of the class?
template <typename T>
inline point3<T> normalize(const point3<T> &object) {
    //float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return object / object.Length();
}


template <typename T>
class point2 {

    public:
        
        point2() {x = y = 0; }
    
        point2(T xx, T yy) : x(xx), y(yy) {  }

        //getters/setters
    
        point2(const point2<T> &object) {
            x = object.x;
            y = object.y;
        };
    
        
        point2<T>& operator=(const point2<T> &object) {
            x = object.x;
            y = object.y;
            return *this;
        };
         
    
        T operator[](unsigned int index) const {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x;
            return y;
        };
        
        T &operator[](unsigned int index) {
            assert(index >= 0 && index <= 2);
            if (index == 0) return x;
            return y;
        };
    
        //opperators (overloading)
    
        point2<T> operator+(const point2<T> &object) const {
            return point(x + object.x, y + object.y);
        };

        point2<T> operator-(const point2<T> &object) const {
            return point(x - object.x, y - object.y);
        };
          
    float Length() const { return std::sqrt(x * x + y * y); }
    
    T x, y, z;
    

};

typedef point2<float> point2f; //are these neeeded?
typedef point2<int> point2i;


template <typename T>
inline std::ostream &operator<<(std::ostream &os, const point2<T> &object) {
    os << "[ " << object.x << ", " << object.y  << ", " << " ]";
    return os;
}


#endif /* point.hpp */
