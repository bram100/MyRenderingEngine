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

class BRDF{
    //color3 kd, ks, ka, kr; //initilizing color3 4 times
public:
    color3 diffuse, specular, ambient, mirror;

    BRDF() :    diffuse(),
                specular(),
                ambient(),
                mirror()
    {}
    
    BRDF(const color3& diffuse, const color3& specular, const color3& ambient, const color3& mirror)
        : diffuse(diffuse), specular(specular), ambient(ambient), mirror(mirror)
    {}
    
    
      const color3& getAmbient() const {
          return ambient;
      }


};


#endif /* BRDF_hpp */
