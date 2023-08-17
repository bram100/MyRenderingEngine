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
class PointLights : public Lights {
public:
    PointLights(const vector3<float>& lightPos, const color3& lightColor, vector3<float> attenuation, const transformation lightToWorld)
        : Lights(lightToWorld, attenuation), lightPos(lightPos), lightColor(lightColor) {}

    ~PointLights();

    void generateLightRay(localGeo& local, ray* lightRay, color3* lightColor) override {
        
       // epsilonj = 0.0000001f * direction
       // point3<float> epsilonPos(local.pos.x + 0.0000001f, local.pos.y + 0.0000001f,  local.pos.z + 0.0000001f);//
        
        vector3<float> vectorPos(local.pos.x , local.pos.y, local.pos.z);

        
        //direction
        vector3<float> direction = normalize( lightPos - local.pos);// MathOperations::vectorFloatSub(local.pos, 0.00000000000000001f) );

        //
        vector3<float> directionEpsilon = MathOperations::floatVector3Multiply(.0001, direction);
        
        //origin altered by epsilon * shadowRayDirection
        vector3<float> lookFromEpsilon = MathOperations::vectorVectorAdd(vectorPos, directionEpsilon);
        
        *lightRay = ray(lookFromEpsilon, direction,  infinity, (infinity * -1));

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
