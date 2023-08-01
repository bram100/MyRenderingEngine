//
//  sample.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#ifndef sample_hpp
#define sample_hpp

#include <stdio.h>
#include <iostream>


class sample2
{
public:
        float x, y;
    
        sample2() : x(0), y(0) {}
        sample2(float x, float y) : x(x), y(y) {}
    
    sample2 (const sample2 &sampleObject) {
        x = sampleObject.x;
        y = sampleObject.y;
    };
};

inline std::ostream &operator<<(std::ostream &os, const sample2 &sampleObject) {
    os << "[ " << sampleObject.x << ", " << sampleObject.y << " ]";
    return os;
}

#endif /* point.hpp */
