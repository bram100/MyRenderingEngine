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


#include "primitive.hpp"
#include "geometricPrimitive.hpp"

#include "scene.hpp"

#include "material.hpp"

bool isThereIntersect = false;

int counting = 0;

intersection currentIntersect;
localGeo localGeo;
intersection closestIntersect;
bool hitAnything;
float closestTHit;

ray lightRay;
color3 lightColor;
BRDF brdf;

extern Scene scene;
extern std::vector<std::shared_ptr<GeometricPrimitive>> geometricPrimitives;

std::shared_ptr<Material> currentMaterial;



void trace(ray& ray, int depth, color3* color3) {
    hitAnything = false;
    closestTHit = std::numeric_limits<float>::infinity();
    if (depth > maxDepth) { //depth as in bounces?
        //presently this doesnt do anything
        color3->r = 0.f;
        color3->g = 0.f;
        color3->b = 0.f;
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
            color3->r = 0.f;
            color3->g = 0.f;
            color3->b = 0.f;
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
                        
                        //break
                    }
                    
                    if (inShadow == false) {
                        
                    }
                    
                    
                }
                
                
            
                    if (!inShadow) {
                        
                        *color3 += currentMaterial->shading(closestIntersect.localGeo, lightRay, lightColor);
                
                    }
                }
                
                
           // }
        }
        /*
         else {
         color3->r = 0.f;
         color3->g = 0.f;
         color3->b = 0.f;
         return false;
         }
         */
        
        
        /*
         if (brdf.emission > 0) {
         reflectRay = createReflectRay(in.local, ray);
         // Make a recursive call to trace the reflected ray
         trace(reflectRay, depth+1, &tempColor);
         *color += brdf.emission * tempColor;
         }
         */
    
    };
