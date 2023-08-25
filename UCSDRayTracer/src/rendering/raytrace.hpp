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
#include "material.hpp"
#include "math.hpp"

void trace(ray& ray, int depth, color3* color);





//std::shared_ptr<Material>  amaterial ;

#endif /* raytrace_hpp */
