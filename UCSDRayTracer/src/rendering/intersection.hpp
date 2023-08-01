//
//  intersection.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/18/23.
//

#ifndef intersection_hpp
#define intersection_hpp

#include "localGeo.hpp"
#include "primitive.hpp"

class primitive;

class intersection {
public:
    localGeo localGeo;
    std::shared_ptr<primitive> primitive;
    
};

#endif /* intersection */
