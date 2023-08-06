//
//  directional.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#include "directionalLight.hpp"
#include "lights.hpp"
#include "transform.hpp"
#include "color.hpp"
#include "objParameters.hpp"

std::shared_ptr<Lights> createDirectionalight(const transformation *l2w, const objParamMap &params) {

    
    vector3<float> lightDir = params.findOneVector3F("position", vector3<float>()) ;
    color3 lightColor = params.findOneColor3("color", color3()) ;
    vector3<float> attenuation = params.findOneVector3F("attenuation", vector3<float>()) ;
    
    return std::make_shared<DirectionalLights>(lightDir, lightColor, attenuation, *l2w);

}

DirectionalLights::~DirectionalLights() {
    // Implementation of the destructor
    // Add any necessary cleanup code here
}


