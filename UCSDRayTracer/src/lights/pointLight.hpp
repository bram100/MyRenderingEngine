//
//  point.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#ifndef pointLight_hpp
#define pointLight_hpp

#include "lights.hpp"
#include "ray.hpp"

class PointLights : public Lights {
public:
    PointLights(const vector3<float>& lightPos, const color3& lightColor, vector3<float> attenuation, const transformation lightToWorld)
        : Lights(lightToWorld, attenuation), lightPos(lightPos), lightColor(lightColor) {}

    ~PointLights();

    void generateLightRay(localGeo& local, ray* lightRay, color3* lightColor) override {
        vector3<float> direction = (lightPos - local.pos);

        // Set up the light ray
        *lightRay = ray(lightPos, direction, infinity, (infinity * -1));

        // Set the light color
        *lightColor = this->lightColor;
    }
    


private:
    vector3<float> lightPos;
    color3 lightColor;
    vector3<float> attenuation; // constant, linear, quadratic
    transformation lightToWorld;
};

std::shared_ptr<Lights> createPointLight(const transformation *lightToWOrld, const objParamMap &params);

#endif
