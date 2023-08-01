//
//  raytrace.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/21/23.
//

#ifndef raytrace_hpp
#define raytrace_hpp

#include <stdio.h>
#include "color.hpp"
#include "ray.hpp"

void trace(ray& ray, int depth, color3* color);
//void trace(sample2 currentSample, int depth, color3 color);

#endif /* raytrace_hpp */
