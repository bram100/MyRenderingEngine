//
//  reflectedRay.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/22/23.
//

#ifndef reflectedRay_hpp
#define reflectedRay_hpp

#include <stdio.h>
#include "ray.hpp"
#include "vector.hpp"
#include "normal.hpp"
#include "localGeo.hpp"

vector3<float> calculateReflectionDirection(const vector3<float>& incidentDirection, const normal<float>& surfaceNormal);

ray createReflectRay(const localGeo& intersectLocalGeo, const ray& incidentRay);

#endif /* reflectedRay_hpp */
