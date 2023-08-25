//
//  directionalLight.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 8/02/23.
//

#ifndef directionalLight_hpp
#define directionalLight_hpp

#include "lights.hpp"

class DirectionalLights : public Lights {
public:
    DirectionalLights(const vector3<float>& dir, const color3& lightColor, const vector3<float>& attenuation, const transformation lightToWorld)
        : Lights(lightToWorld, attenuation), direction(dir), lightColor(lightColor) {}

    ~DirectionalLights();
    void generateLightRay(localGeo& local, ray* lightRay, color3* lightColor) override {
        // For a directional light, the direction is constant for all points in the scene
        //why negative
        vector3<float> lightDir = normalize(direction * -1);
        
        // Generate the light ray with the directional light direction
        *lightRay = ray(local.pos, lightDir,  infinity, (infinity * -1));

        *lightColor = this->lightColor;

        }

private:
    // Directional light attributes
    vector3<float> direction;
    color3 lightColor;
    transformation lightToWorld;

};


std::shared_ptr<Lights> createDirectionalight(const transformation *lightToWOrld, const objParamMap &params);

#endif
