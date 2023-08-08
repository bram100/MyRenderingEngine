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

