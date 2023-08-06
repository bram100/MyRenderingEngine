//
//  vector.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/4/23.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <cmath>
#include "point.hpp"
#include "vector.hpp"
//#include "matrix.hpp"
//value of 1 for the origin and 0 for the direction for 4d vector/ray transformation 

template <typename T>
class point3;

template <typename T>
inline bool isNaN(const T x) {
    return std::isnan(x);
}

template <typename T>
class vector3 {
    public:
        //constructors https://stackoverflow.com/questions/51936650/vector-constructor-example-with-const-pointer
        vector3() {x = y = z = 0; }
    
        vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {  }
    
        bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

        //getters/setters
        vector3(const vector3<T> &object) {
            x = object.x;
            y = object.y;
            z = object.z;
        };
        
    void clear() {
        x = y = z = 0;
    }
    
    
    void ones() {
        x = y = z = 1;
    }


    bool operator!=(const vector3<T>& other) const {
           return (x != other.x) || (y != other.y) || (z != other.z);
       }
    
    
    
    vector3<T>& operator=(const vector3<T>& object) {
        if (this == &object)
            return *this;
        x = object.x;
        y = object.y;
        z = object.z;
        return *this;
    }

    
        vector3<T>& operator=(vector3<T>&& object) {
             assert(!object.HasNaNs());
            x = std::move(object.x);
            y = std::move(object.y);
            z = std::move(object.z);

            return *this;
        }
         
    
    
        void push_back(T value) {
        // Add value to the vector3
        // Implement the logic to add the value to x, y, and z appropriately
            x = value.x;
            y = value.y;
            z = value.z;
        }

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
        vector3<T> operator+(const vector3<T> &object) const {
            return vector3(x + object.x, y + object.y, z + object.z);
        };

        vector3<T> operator-(const vector3<T> &object) const {
            return vector3(x - object.x, y - object.y, z - object.z);
        };
    
    
    vector3<T> operator-(const point3<T> &object) const {
        return vector3(x - object.x, y - object.y, z - object.z);
    };

    
    
    operator vector3<float>*() const {
            return new vector3(x, y, z);
        }

    
    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value>::type* = nullptr>
        vector3<T> operator*(U scalar) const {
            return vector3<T>(scalar * x, scalar * y, scalar * z);
        };

    


    //return a scalar, thus dot product
        T operator*(const vector3<T> &object) const {
        return ((x * object[0]) + (y * object[1]) + (z * object[2]));
    };
    
    T operator*(const point3<T>& point) const {
        return x * point.x + y * point.y + z * point.z;
    }

    
    //cross product
    vector3<T> operator^(const vector3<T>& object) const {
        float crossX = y * object.z - z * object.y;
        float crossY = z * object.x - x * object.z;
        float crossZ = x * object.y - y * object.x;
        return vector3<T>(crossX, crossY, crossZ);
    }
     
    //what are these for? point3 in a vector class?
    operator point3<float>() const {
            return point3(x, y, z);
        }
    
   
    template <typename U>
    vector3<T> operator/(U scalar) const {
                return vector3<T>(x / scalar, y / scalar, z / scalar);
        };
      
    template <typename U>
    vector3<T> operator+(U scalar) const {
        return vector3<T>(x + scalar, y + scalar, z + scalar);
    };


   // operator point3<float>() const;
    operator point3<float>*() const;

    /*operator point3<T>() const {
        return point3<T>{x, y, z};
    }
*/
    float Length() const { return std::sqrt(x * x + y * y + z * z); }
    
    T x, y, z;
    
  

};

typedef vector3<float> Vector3f; //are these neeeded?
typedef vector3<int> Vector3i;

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const vector3<T> &object) {
    os << "[ " << object.x << ", " << object.y  << ", " << object.z << " ]";
    return os;
}

template <typename T>
inline vector3<T> normalize(const vector3<T> &v) {
    return v / v.Length();
}




template <typename T>
class vector4 {

    public:

        vector4() {x = y = z = w = 0; }
    
        vector4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {  }
    
        explicit vector4(const vector3<T>& vec3) : x(vec3.x), y(vec3.y), z(vec3.z), w(1) {}
        explicit vector4(const vector3<T>& vec3, T ww) : x(vec3.x), y(vec3.y), z(vec3.z), w(ww) {}

        bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z) || isNaN(w); }

        //getters/setters
        vector3<T> xyz() const {
            return vector3<T>(x, y, z);
        }

        vector4<T>& operator=(const vector4<T> &object) {
            assert(!object.HasNaNs());
            x = object.x;
            y = object.y;
            z = object.z;
            w = object.w;
        
            return *this;
        };
         
    
        T operator[](unsigned int index) const {
            assert(index >= 0 && index <= 3);
            if (index == 0) return x;
            if (index == 1) return y;
            if (index == 2) return z;
            return w;
        };
        
        T &operator[](unsigned int index) {
            assert(index >= 0 && index <= 3);
            if (index == 0) return x;
            if (index == 1) return y;
            if (index == 2) return z;
            return w;
        };
    
        //opperators
        vector4<T> operator+(const vector3<T> &object) const {
            return vector4(x + object.x, y + object.y, z + object.z);
        };

        vector4<T> operator-(const vector4<T> &object) const {
            return vector4(x - object.x, y - object.y, z - object.z,  w - object.w);
        };

    //return a scalar, thus dot product
    T operator*(const vector4<T> &object) const {
        return ((x * object[0]) + (y * object[1]) + (z * object[2]) + (w * object[3]));
        
    };
     
    
  

    
    
    
    
        template <typename U>
            vector4<T> operator*(U s) const {
                return vector4<T>(s * x, s * y, s * z, s * w);
            };
    
    T operator*(const vector3<T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }


    
        template <typename U>
        vector4<T> operator/(U s) const {
                return vector4<T>(x / s, y / s, z / s, w / s);
        };
      
    float Length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
    
    T x, y, z, w;
    
    typedef vector4<float> Vector4f; //are these neeeded?
    typedef vector4<int> Vector4i;

};

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const vector4<T> &object) {
    os << "[ " << object.x << ", " << object.y  << ", " << object.z << ", " << object.w << " ]";
    return os;
}


#endif /* vector_hpp */
