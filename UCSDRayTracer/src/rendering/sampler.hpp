//
//  sampler.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#ifndef sampler_hpp
#define sampler_hpp

#include <stdio.h>
#include "sampler.hpp"
#include "sample.hpp"
#include "variables.hpp"

class sampler {
public:
    sampler(int width, int height);
    
    bool getSample(sample2* currentSample);

    int width;
    int height;
    
private:
    int currentX;
    int currentY;
};


#endif /* sampler_hpp */
