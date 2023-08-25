//
//  reflectedRay.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/22/23.
//

#include "reflectedRay.hpp"
#include "math.hpp"

vector3<float> calculateReflectionDirection(const vector3<float>& incidentDirection, const normal<float>& surfaceNormal) {

    
    float dotProduct = MathOperations::dotProduct(incidentDirection, surfaceNormal);

    vector3<float> reflectionDirection = MathOperations::vectorVectorSub(incidentDirection, 2.0f * dotProduct * surfaceNormal);

    return reflectionDirection;

    
}

ray createReflectRay(const localGeo& intersectLocalGeo, const ray& incidentRay) {
    
    
    vector3<float> noramlizeIncident = normalize(incidentRay.lookAt);
    vector3<float> reflectionDirection = (calculateReflectionDirection( noramlizeIncident, intersectLocalGeo.normal));
    
    
    
    
    
  //  std::cout << intersectLocalGeo.pos.x<< std::endl;
    
    
    
    
    
   // point3<float> holding(intersectLocalGeo.pos.x + .0001, intersectLocalGeo.pos.y + .0001, intersectLocalGeo.pos.z + .0001);
    
    
    
    
    
    point3<float> adjustedOrigin = intersectLocalGeo.pos + MathOperations::floatVector3Multiply(0.0001, reflectionDirection);

    
    
    
    
    
    
    
    
    ray reflectedRay(adjustedOrigin,  reflectionDirection, 0.001, -1*infinity);
    
    return reflectedRay;
}
