//
//  point.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#ifndef pointLight_hpp
#define pointLight_hpp

#include "lights.hpp"


class PointLights : public Lights {
public:
    PointLights(const vector3<float>& lightPos, const color3& lightColor, vector3<float> attenuation, const transformation lightToWorld)
        : Lights(lightToWorld, attenuation), lightPos(lightPos), lightColor(lightColor) {}

    ~PointLights();

    void generateLightRay(localGeo& local, ray* lray, color3* lcolor) override {
        // For a point light, the light ray's direction is from the light position to the point in the scene
        *lray = ray(/* calculate the direction of the light ray from the local geometry and light position */);
        *lcolor = lightColor;
    }
    


private:
    vector3<float> lightPos;
    color3 lightColor;
    vector3<float> attenuation; // constant, linear, quadratic
    transformation lightToWorld;
};

std::shared_ptr<Lights> createPointLight(const transformation *lightToWOrld, const objParamMap &params);

#endif
