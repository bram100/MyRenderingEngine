//
//  lights.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#include <iostream>


#include "math.hpp"
#include "readCommand.hpp"
#include "scene.hpp"
#include "transform.hpp"
#include "directionalLight.hpp"
#include "pointLight.hpp"


extern Scene scene;

void makeLights(const std::string &name, const transformation *lightToWorld, const objParamMap &paramSet) {
    
    //intersection intersection;
    std::shared_ptr<Lights> aLight;

    if (name == "point") {
        aLight = createPointLight(lightToWorld, paramSet);
    }
    
    else if (name == "directional" ) {
        aLight = createDirectionalight(lightToWorld, paramSet);
    }

    else {
        throw std::invalid_argument("error reading light");
    }
        
    scene.addLight(aLight);
        
    
    
    aLight.reset();

    
 }


Lights::~Lights() {
    // Implementation of the destructor
    // Add any necessary cleanup code here
}


void generateLightRay(localGeo& local, ray* lray, color3* lcolor) {
    // Implementation of the generateLightRay function for PointLights
    // Add code to calculate the light ray direction and color
    *lray = ray(/* calculate the direction of the light ray from the local geometry and light position */);
    //*lcolor = lightColor;
}
