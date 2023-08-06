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

#include "geometricPrimitive.hpp"
#include "scene.hpp"

bool isThereIntersect = false;

int counting = 0;

intersection currentIntersect;
localGeo localGeo;

bool hitAnything;
float closestTHit;

extern Scene scene;
extern std::vector<std::shared_ptr<GeometricPrimitive>> geometricPrimitives;


void trace(ray& ray, int depth, color3* color3) {
    hitAnything = false;
    closestTHit = std::numeric_limits<float>::infinity();
    if (depth > maxDepth) { //depth as in bounces?
        
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
        
        if (p->intersect(ray, &tHit, &currentIntersect)) {
            hitAnything = true;
            currentIntersect.localGeo = localGeo;
            if (tHit < closestTHit) {
                *color3 = p->getMaterial()->getAmbient();
                
                closestTHit = tHit;
            }
        }
    }
     
        if (hitAnything == true) {
           // currentColor.b = 100.f;

            return true;
            }
        
        else {
            color3->r = 0.f;
            color3->g = 0.f;
            color3->b = 0.f;

            return false;
        }

    };
