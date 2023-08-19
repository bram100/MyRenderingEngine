//
//  color.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/25/23.
//

#ifndef color_hpp
#define color_hpp

#include <stdio.h>
#include <iostream>
#include "vector.hpp"


class color3
{
    public:
        int r, g, b;
        color3() : r(0), g(0), b(0) {}
        color3(int r, int g, int b) : r(r), g(g), b(b) {}
    
    
        // Copy constructor
        color3(const color3& other) : r(other.r), g(other.g), b(other.b) {}

    
    
       // Assignment operator
       color3& operator=(const color3& other) {
           if (this != &other) {
               r = other.r;
               g = other.g;
               b = other.b;
           }
           return *this;
       }
    
        bool operator==(const color3& other) const {
            return r == other.r && g == other.g && b == other.b;
        }

        bool operator!=(const color3& other) const {
            return (r != other.r) || (g != other.g) || (b != other.b);
        }
    /*
        color3& operator*(const color3& other) const {
            if (this != &other) {
                r *= other.r;
                g *= other.g;
                b *= other.b;
            }
            return *this;
        }
*/
    
        color3 operator*(float scalar) const {
            
            return color3(r * scalar, g * scalar, b * scalar);
        }
        
    
        color3 operator*(const color3& other) const {
            
            return color3(r * other.r, g * other.g, b * other.b);
        }
    
        color3 operator*(const vector3<float>& vec) const {
            return color3(r * vec.x, g * vec.y, b * vec.z);
        }

    

    
        color3& operator+=(const color3& other) {
            r += other.r;
            g += other.g;
            b += other.b;
            return *this;
        }


};

inline std::ostream &operator<<(std::ostream &os, const color3 &object) {
    os << object.r << " " << object.g << " " << object.b;
    return os;
}

color3 convertFloatToColor(const float floatValues[10]);


#endif /* color_hpp */

