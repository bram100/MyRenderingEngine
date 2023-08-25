//
//  lights.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#ifndef lights_hpp
#define lights_hpp

#include "color.hpp"
#include "vector.hpp"
#include "localGeo.hpp"
#include "ray.hpp"
#include "objParameters.hpp"
#include "transform.hpp"



class Lights {
public:
    Lights();
    Lights(const transformation lightToWorld, const vector3<float>& attenuation)
        : lightToWorld (lightToWorld), attenuation(attenuation) {}
    virtual ~Lights();

    virtual void generateLightRay(localGeo& local, ray* currentRay, color3* currentColor) = 0;
    
    
    const vector3<float>& getAttenuation() const {
           return attenuation;
       }

    //why protected
    protected:
    vector3<float> attenuation;
    transformation lightToWorld;
};




void makeLights(const std::string &name, const transformation *lightToWorld, const objParamMap &paramSet);

extern std::vector<std::shared_ptr<Lights>> lightContainer;

#endif // lights_hpp
