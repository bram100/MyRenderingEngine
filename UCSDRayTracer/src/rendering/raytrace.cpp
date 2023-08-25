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

    if (depth > maxDepth) {

        exitColor3->r = 0.f;
        exitColor3->g = 0.f;
        exitColor3->b = 0.f;
    }
     
    //for (int i = 0; i < scene.geometricPrimitives.size(); ++i) {
    for (const auto& p : scene.geometricPrimitivesVec){
        
        //const auto& p = scene.geometricPrimitives[i];
        //const auto& transformationFromStack = scene.transformationStack[i];
        
        currentIntersect.primitive = p;
        //apply transformation to object
        
        //multiply transfor
        
        //p->applyTransformationToObject(transformationFromStack);
        if (!p->intersect(ray, &tHit, &currentIntersect)) {
            exitColor3->r = 0.f;
            exitColor3->g = 0.f;
            exitColor3->b = 0.f;
            
        }
        else {
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
                    
                }
                //directional lights
                else{
                    attenuationFloat = 1;
                }
          
                *exitColor3 += (currentMaterial->shadingShadows(closestIntersect.localGeo, lightRay, lightColor)) * attenuationFloat;// *  currentAttenuation;
                    
                
            }
            
        }
        
    }
    
    if (depth == 0){
        depth0Color = *exitColor3;
        depth0Color.normalize();
    }
    if (hitAnything == true) {
        
        
        if (depth < maxDepth) {
            
            reflectRay = createReflectRay(closestIntersect.localGeo, ray);
            
            depth++;
            
            color3 tempColor(0, 0, 0);
            trace(reflectRay, depth, &tempColor);
            
            globalColor += ( currentMaterial->aBRDF.specular * tempColor);
            globalColor.normalize();
        }
        
        
    }
    *exitColor3 = depth0Color ;
    exitColor3->normalize();

            
        *exitColor3 +=  color3(globalColor.r/5, globalColor.g/5, globalColor.b/5);
    

};




