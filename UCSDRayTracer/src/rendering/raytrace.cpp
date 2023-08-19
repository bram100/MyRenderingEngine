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
#include <cmath>
bool isThereIntersect = false;

int counting = 0;

intersection currentIntersect;
localGeo localGeo;
intersection closestIntersect;
vector3<float> currentAttenuation;
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
    vector3<int> cVector(0, 0, 1);//maybe put this somewhere else??
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
                        break;
                    }
                    
                }
                    //no shape intersect, thus visslible
                    if (!inShadow) {
                        if (/*std::shared_ptr<PointLight> pointLight =*/ std::dynamic_pointer_cast<PointLight>(l)) {
                            
                            //change cVector to 0, 0, 1
                            cVector.z = 1;
                            
                            vector3<float> lightPos = lightRay.lookAt /* position of the light source */;
                            point3 pointPos = closestIntersect.localGeo.pos /* position of the point you're calculating for */;

                            vector3<float> diff = lightPos - pointPos;
                            float r = diff.Length(); // Calculate the length of the vector

                            
                            
                            currentAttenuation = lightRay.lookAt / (cVector.x + cVector.y * r + std::pow(cVector.z, r));
                            

                        }

                        
                        *color3 += (currentMaterial->shadingShadows(closestIntersect.localGeo, lightRay, lightColor));// * currentAttenuation;
                
                    }
                
                
                }
            *color3 += currentMaterial->ambient;
            
            *color3 += currentMaterial->aBRDF.emission;

            //*color3 += currentMaterial->shading(closestIntersect.localGeo, lightRay, lightColor);

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
