//
//  shape.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/7/23.
//

#include <iostream>

#include "math.hpp"

#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "readCommand.hpp"
//#include "camera.hpp"
#include "geometricPrimitive.hpp"
#include "scene.hpp"

int triMeshCount;

int countingh = 0;
int countingn = 0;
//extern matrix4& worldToCamera;

extern Camera camera;
extern Scene scene;

extern std::shared_ptr<Material> materialParsed;


int nShapesCreated;
Shapes::~Shapes() {}
Shapes::Shapes() {}

Shapes::Shapes(const transformation *objectToWorld, const transformation *worldToObject)
    : objectToWorld(objectToWorld),
      worldToObject(worldToObject)
       {
           //this needed???
           ++nShapesCreated;
           
           matrix4& worldToCamera = camera.cameraToWorld;// camera.worldToCamera;

          // cameraToWorld = inverse(worldToCamera);
               transformation cameraShapeTransformation = *objectToWorld ^ worldToCamera;
          

} 

extern float closestTHit;
extern bool hitAnything;
extern transformationSet curTransform; //should probably move where this is defined
int count2 = 0;
int a, b = 0;

//intersection in object space
bool Shapes::intersect(const ray& ray, float* tHit, localGeo* localGeo) const {

}
    
    /*
     Same as intersect, but just return whether there is any intersection or not
     */

bool Shapes::intersectP(const ray& ray) const {
    
}


void createTransformationMatrix(const vector3<float>& translate, const vector3<float>& rotation, const float axis, const vector3<float>& scale, const int i) {

    transformation transformationMatrix; //should be identity matrix
       
    transformationMatrix.mt = camera.cameraToWorld;

    //(TRS is the proper order but that doesnt work with
    // translation
    transformation translationMatrix;
    
    translationMatrix.translation(translate);
    transformationMatrix *= translationMatrix;
    
    //rotation
    transformation rotationMatrix;
    rotationMatrix.rotation(axis, rotation);
    transformationMatrix *= rotationMatrix;

    // Apply scaling
    transformation scaleMatrix;
    scaleMatrix.scaling(scale);
    transformationMatrix *= scaleMatrix;


    transformationMatrix.updateInverse();
    curTransform[i] = transformationMatrix;
    
    
    
}


void makeShapes(const std::string &name, const transformation *object2World, const transformation *world2Object, objParamMap &paramSet) {
    std::vector<std::shared_ptr<Shapes>> vecShapes;
    intersection intersection;
    std::shared_ptr<Shapes> aShape;
    
    aShape.reset();
    vecShapes.clear();
    
    if (name == "sphere") {
        aShape = createSphereShape(object2World, world2Object, paramSet);
    }
    
    else if (name == "temp" ) {
        //other shape type
    }
    
    if (aShape != nullptr) {
        vecShapes.push_back(aShape);
        
    }
    
    else if  (name == "triangleMesh") {
        vecShapes = createTriangleMeshShape(object2World, world2Object, paramSet, 0);
        
        triMeshCount++;
        std::cout << "triagnle Mesh created " << triMeshCount << std::endl;
    }

    else {
        throw std::invalid_argument("error reading accelerator");
    }
    
    for (const auto& shape : vecShapes) {
        
        std::shared_ptr<GeometricPrimitive> geometricPrimitive = std::make_shared<GeometricPrimitive>(shape, materialParsed);

        scene.addGeometricPrimitive(geometricPrimitive);
        
    }
    
 }


// Multiplication of transformations

