//
//  raytrace.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/21/23.
//

#include "raytrace.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "readCommand.hpp"
#include "sample.hpp"
#include "shape.hpp"

#include "lights/pointLight.hpp"

#include "primitive.hpp"
#include "geometricPrimitive.hpp"

#include "scene.hpp"

#include "material.hpp"
#include "reflectedRay.hpp"

#include <cmath>
bool isThereIntersect = false;

int dividing;
color3 redcolor(255.f, 0, 0);
color3 holdingColor;
int counting = 0;
color3 tempColor;
float attenuationFloat;

intersection currentIntersect;
localGeo localGeo;
intersection closestIntersect;
vector3<float> currentAttenuation;
bool hitAnything;
float closestTHit;
extern color3 globalColor;
ray reflectRay;
ray lightRay;
color3 lightColor;
BRDF brdf;
color3 depth0Color;
extern Scene scene;
extern std::vector<std::shared_ptr<GeometricPrimitive>> geometricPrimitives;

std::shared_ptr<Material> currentMaterial;

int countingf;

void trace(ray& ray, int depth, color3 *exitColor3) {
    hitAnything = false;
    closestTHit = std::numeric_limits<float>::infinity();

    exitColor3->r = 0.f;
    exitColor3->g = 0.f;
    exitColor3->b = 0.f;

    
    if (depth >= 5) {

        exitColor3->r = 0.f;
        exitColor3->g = 0.f;
        exitColor3->b = 0.f;
        
        return;
    }
     
    //intersection testing between camera and object
    //for (int i = 0; i < scene.geometricPrimitives.size(); ++i) {
    for (const auto& p : scene.geometricPrimitivesVec){
        
        //const auto& p = scene.geometricPrimitives[i];
        //const auto& transformationFromStack = scene.transformationStack[i];
        
        currentIntersect.primitive = p;
        //apply transformation to object
        
        //multiply transfor
        
        //if no intersect, make color black
        //this can probably be
        //p->applyTransformationToObject(transformationFromStack);
        
        
        if (p->intersect(ray, &tHit, &currentIntersect)) {

            hitAnything = true;
            
            if (tHit < closestTHit) {

                closestTHit = tHit;

                closestIntersect = currentIntersect;

                
                currentMaterial = currentIntersect.primitive->getMaterial();

            }
            
        }
        }

        bool inShadow = false;

    if (hitAnything) {
        
        for (const auto& l : scene.lightsVec){
            
            l->generateLightRay(closestIntersect.localGeo, &lightRay, &lightColor);
            
            //for every shape
            for (const auto& p : scene.geometricPrimitivesVec) {
                //check if shape intersects with the lightRay
                //if intersect is there, then shadow must be true
                
                //it needs to loop only through the sapes not looped through
                if (p->intersectP(lightRay)) {
                    inShadow = true;
                    break;
                }
                
            }
            
            //no shape intersect, thus visslible
            *exitColor3 += currentMaterial->ambient;
            *exitColor3 += currentMaterial->aBRDF.emission;
            
            
            if (!inShadow) {
                
                if ( std::dynamic_pointer_cast<PointLight>(l)) {
                    
                    vector3<float> cVector = l->getAttenuation();
                    
                    vector3<float> diff =   closestIntersect.localGeo.pos - lightRay.lookAt; //LightPos - intersect
                    float r = diff.Length(); // Calculate the length of the vector
                    
                    float L = 1; //lightRay.lookAt
                    attenuationFloat =  L / (cVector.x + cVector.y * r + cVector.z * std::pow(r, 2));
                    
                    if (depth > 0) {
                        
                    }
                }
                //directional lights
                else{
                    attenuationFloat = 1;
                    
                }
          
                *exitColor3 += (currentMaterial->shadingShadows(closestIntersect.localGeo, lightRay, lightColor)) ;//* attenuationFloat;// *  currentAttenuation;
                if (attenuationFloat != 1) {
                    
                }
                
            }
        }
        
    }
    
    
    if (hitAnything == true) {
        if (depth < maxDepth) {
            
            reflectRay = createReflectRay(closestIntersect.localGeo, ray);
            
            depth++;
            
            color3 tempColor(0, 0, 0);
            trace(reflectRay, depth, &tempColor);
            
            //tempColor.r/dividing
            globalColor += ( currentMaterial->aBRDF.specular * tempColor  * attenuationFloat);
            
            
            globalColor.normalize();
            dividing++;

        }
        
        
    }
    *exitColor3;// = depth0Color ;

    color3 fuck =color3(globalColor.r/dividing, globalColor.g/dividing, globalColor.b/dividing);
    
    fuck.normalize();
    *exitColor3 +=  fuck;
    
    
    dividing = 0;
};




