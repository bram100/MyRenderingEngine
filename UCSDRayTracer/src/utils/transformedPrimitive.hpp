//
//  transformedPrimitive.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 6/29/23.
//

#ifndef transformedPrimitive_hpp
#define transformedPrimitive_hpp

#include <stdio.h>
#include "primitive.hpp"
#include "shape.hpp"
#endif /* transformedPrimitive_hpp */
//https://pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration

class transformedPrimitive : public primitive {
    transformation objToWorld, worldToObj;

};

