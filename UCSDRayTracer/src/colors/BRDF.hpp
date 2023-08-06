//
//  BRDF.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#ifndef BRDF_hpp
#define BRDF_hpp

#include <stdio.h>
#include "color.hpp"

//just storing color right now, not the actual BRDF

// kd, ks, ka are diffuse, specular and ambient component respectively
// kr is the mirror reflection coefficient


//BRDF models how light interacts with a single point on a surface, considering the incident light direction and the outgoing light direction.

//Rendering Equation: It is a more general equation that describes the total light leaving a point in a scene -


//BRDF is a function that describes the ratio of reflected radiance (outgoing light) to the incident radiance (incoming light) at a surface point for reflection only.
//ok, this is not
class BRDF{
    //color3 kd, ks, ka, kr; //initilizing color3 4 times
public:
    color3 diffuse, specular, shininess, emission;

    BRDF() :    diffuse(),
                specular(),
                shininess(),
                emission()
    {}
    
    BRDF(const color3& diffuse, const color3& specular, const color3& shininess, const color3& emission)
        : diffuse(diffuse), specular(specular), shininess(shininess), emission(emission)
    {}
    
    
     
    
    const color3& getdiffuse() const {
        return diffuse;
    }



};



#endif /* BRDF_hpp */
