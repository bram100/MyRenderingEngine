//
//  localGeo.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/19/23.
//

#ifndef localGeo_hpp
#define localGeo_hpp

#include <stdio.h>

#include "point.hpp"
#include "normal.hpp"
#include "localGeo.hpp"

/*
 Store the local geometry at the intersection point. May need to store
other quantities (eg. texture coordinate) in a more complicated
raytracer.
*/

//geometric information at an intersection point

class localGeo {
public:
    point3<float> pos;
    normal<float> normal;
};

#endif /* localGeo_hpp */
