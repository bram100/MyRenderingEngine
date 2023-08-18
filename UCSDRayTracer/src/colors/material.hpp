//
//  material.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include "BRDF.hpp"
#include "localGeo.hpp"
#include "ray.hpp"


class Material {
public:
    
    Material() {}
    Material(const BRDF& brdf, color3 ambient) : aBRDF(brdf), ambient(ambient) {}

    
    const color3& getAmbient() const {
        return ambient;
    }

    
    color3 shading(const localGeo& intersection, const ray& lightRay, const color3& lightColor);

    color3 shadingDiffuse(const localGeo& intersection, const ray& lightRay, const color3& lightColor);

    
    BRDF aBRDF;
    color3 ambient;
    //add volumetric scattering to material class??
};

void getBRDF(localGeo& local, BRDF* brdf);



/*
 Class for storing material. For this example, it just returns a constant material regardless of what local is. Later on, when we want to support texture mapping, this need to be modified.
*/

#endif /* material_hpp */
