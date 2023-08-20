//
//  scene.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//
#include <thread>
#include "thread.hpp"


#include "scene.hpp"
#include "film.hpp"

#include "ray.hpp"
#include "raytrace.hpp"
using namespace std;



class Camera;
extern Camera camera;

color3 currentColor;

int currentFrame = 0;

void Scene::addGeometricPrimitive(std::shared_ptr<GeometricPrimitive> geometricPrimitive) {
    geometricPrimitivesVec.push_back(geometricPrimitive);
}

void Scene::addLight(std::shared_ptr<Lights> aLight) {
    lightsVec.push_back(aLight);
}

void Scene::renderer() {
        sampler sampler(w, h); //width height
        
    
        int current = 0;
        int total = w*h;
    
   // for (int i = 0; i < frameNumber; i++) { std::cout << "frame " << currentFrame <<  "of " << frameNumber << std::endl;;
        

    while (!sampler.getSample(&currentSample)) {
        
        current++;
        int percent = (current*100)/total;
        std::cout << "Percentage complete: " << percent << "%" << " [ " << current << " of " << total << " pixels ]" << std::endl;
        
            camera.generateRay(currentSample, &currentRay); //eye position
            
            trace(currentRay, maxDepth, &currentColor);
            
            commit(currentSample, &currentColor);
            // std::cout << "Pixel " << k << " of " << j << std::endl; //progress check
        }
        
        //currentFrame++;
        
    //}
}


