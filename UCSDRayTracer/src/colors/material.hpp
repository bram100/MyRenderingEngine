//
//  material.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "brdf.hpp"
#include "localGeo.hpp"

class Material {
public:
    BRDF aBRDF;
    
    Material() {}
    Material(const BRDF& brdf) : aBRDF(brdf) {}

    
    const color3& getAmbient() const {
        
        return aBRDF.getAmbient();
    }

    //add volumetric scattering to material class??
};

void getBRDF(localGeo& local, BRDF* brdf);

/*
 Class for storing material. For this example, it just returns a constant material regardless of what local is. Later on, when we want to support texture mapping, this need to be modified.
*/

#endif /* material_hpp */
