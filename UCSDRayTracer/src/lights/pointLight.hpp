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
#include "math.hpp"

inline int currentA;
class PointLight : public Lights {
public:
    PointLight(const vector3<float>& lightPos, const color3& lightColor, vector3<float> attenuation, const transformation lightToWorld)
        : Lights(lightToWorld, attenuation), lightPos(lightPos), lightColor(lightColor) {}

    ~PointLight();

    //point light - shines light at a point
    void generateLightRay(localGeo& local, ray* lightRay, color3* lightColor) override {

        //convert intersection to point to vector
        vector3<float> vectorPos(local.pos.x , local.pos.y, local.pos.z);

        //noramlize lookAt, normalize direction
        vector3<float> lookAtDirection = normalize( lightPos - local.pos);
        
        //create epsilon lookAt vector
        vector3<float> lookAtDirectionEpsilon = MathOperations::floatVector3Multiply(0.001, lookAtDirection);
        
        //alter lookFrmo by epsilon lookAt vector
        vector3<float> lookFromEpsilon = MathOperations::vectorVectorAdd(vectorPos, lookAtDirectionEpsilon);
        
        
        
        //lookFrom is intersection point altered by epsilon * direction
        //lookAt is lightPos - intersection
        *lightRay = ray(lookFromEpsilon, lookAtDirection,  infinity, (infinity * -1));

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
