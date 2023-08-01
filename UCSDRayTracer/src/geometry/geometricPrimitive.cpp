//
//  geometricPrimitive.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/27/23.
//

#include "geometricPrimitive.hpp"
#include <iostream>
#include "ray.hpp"

#include "intersection.hpp"
#include "math.hpp"
#include "localGeo.hpp"

//this intersection is for determining the exact lcoation of the intersect. Intersection with shape class returns a binary, this returns an x,y,z normal or something or other 
bool GeometricPrimitive::intersect(ray& currentRay,  float* tHit, intersection* intersct) {
    
    if (shape->intersect(currentRay, tHit, &(intersct->localGeo)))
        return true;

    
    if (*tHit == 1.f) {
         std::cout << "tHit value changed" << std::endl;
     }
}



void GeometricPrimitive::getBRDF(localGeo& local, BRDF* brdf) {
    //holding
    
}

//sets the primitive member variable of the intersct object to point to the same object as the this pointer. This can be useful in cases where the intersct object needs to keep track of the primitive it intersects with, and the this pointer points to that primitive.

//convert intersection point to world space
