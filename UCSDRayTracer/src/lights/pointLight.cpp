//
//  point.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#include "pointLight.hpp"
#include "lights.hpp"
#include "transform.hpp"
#include "color.hpp"
#include "objParameters.hpp"

std::shared_ptr<Lights> createPointLight(const transformation *l2w, const objParamMap &params) {

    
    vector3<float> lightPos = params.findOneVector3F("position", vector3<float>()) ;
    color3 lightColor = params.findOneColor3("color", color3()) ;
    vector3<float> attenuation = params.findOneVector3F("attenuation", vector3<float>()) ;
    
    return std::make_shared<PointLights>(lightPos, lightColor, attenuation, *l2w);


}
PointLights::~PointLights() {
    // Implementation of the destructor
    // Add any necessary cleanup code here
}

