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

 color3 tempColorA;
 color3 tempColorB;
 color3 tempColorC;
 color3 tempColorD;
 color3 tempColorE;
 color3 tempColorF;

color3 globalColor;
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
        
        int currentDepth = 0;

        current++;
        int percent = (current*100)/total;
        std::cout << "Percentage complete: " << percent << "%" << " [ " << current << " of " << total << " pixels ]" << std::endl;
        
            camera.generateRay(currentSample, &currentRay); //eye position

        bool reflectedRay = false;
            trace(currentRay, currentDepth, &currentColor);
                
        if (currentDepth != 0) {
            std::cout << "currentdepth : " << currentDepth << std::endl;
        }
     
        
        
       // std::cout << "final color " << currentColor << std::endl;
        
            commit(currentSample, &currentColor);
            // std::cout << "Pixel " << k << " of " << j << std::endl; //progress check
        globalColor = color3(0,0,0);
        }
    
        
        //currentFrame++;
        
    //}
}


