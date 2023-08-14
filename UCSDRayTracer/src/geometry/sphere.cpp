//
//  sphere.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 4/9/23.
//

#include "sphere.hpp"
#include "math.hpp"
#include "readCommand.hpp"
#include "transform.hpp"
extern Camera camera;


/*
 transformation holding = *objectToWorld ^ camera.cameraToWorld;
 matrix4 holding2 = holding.minvt;
 */
bool sphere::intersect(const ray &currentRay, float *tHit, localGeo *localGeoPos) const
{
        //testingTransform.minvt;
    ray transformedRay;
    
    
    transformedRay.lookAt = normalize(MathOperations::matrixVector( worldToObject->mt, currentRay.lookAt,  0));
    
    transformedRay.lookFrom = (MathOperations::matrixVector(worldToObject->mt, currentRay.lookFrom,  1));

    
    float t0 = 0;
    float t1 = 0;
    
    
    point3<float> transformedCenter = center;// (MathOperations::matrixVector(worldToObject->mt, center,  0));

    //point3<float> transformedCenter = center;// multPointMatrix<float>(camera.worldToCamera, center); //i may need to fix this

    vector3<float> L = transformedRay.lookFrom - transformedCenter; //vector from the ray's origin to the center of the sphere
    

    float a = transformedRay.lookAt*transformedRay.lookAt; //normaly equal to 1
    float b = 2 * (transformedRay.lookAt*L); //allignment/similarity between ray origin and sphere
    float c = (L*L) - (radius * radius); //checking L against radius of sphere
    
    //std::cout << "lookAt" << ray.lookAt << std::endl;
    
    
   // std::cout << " a: " << a << " b: " << b << " c: " << c << " t0: "<< t0 << " t1: " <<t1 << std::endl;
    if (!math.solveQuadratic(a, b, c, t0, t1)) {
        return false;
    }

    if (t0 > t1) std::swap(t0, t1);
    
    if (t0 < 0) {
        
        t0 = t1; // if t0 is negative, let's use t1 instead
        *tHit = t0;
        //std::cout << tHit << std::endl;
        
        if (t0 < 0)
    
            return false;
        
    }

    //localGeoPos->pos = transformedRay.pointAt(t0);
    
    localGeoPos->pos = MathOperations::matrixVector(objectToWorld->mt, transformedRay.pointAt(t0), 1.f);

    vector3<float> normalVector = (transformedRay.pointAt(t0) - transformedCenter);
    

    
    //localGeoPos->normal = MathOperations::transformation3Matrix(normal<float>(normalVector.x, normalVector.y, normalVector.z), objectToWorld->minvt);
    
    
   // normal<float> worldNormal = transformation::Transpose(objectToWorld->minvt) * normal<float>(normalVector.x, normalVector.y, normalVector.z);

    localGeoPos->normal = MathOperations::matrixVector(transformation::Transpose(objectToWorld->minvt), normalVector, 0.f);

                      
    

    *tHit = t0;

    
    return true;
    
}


//don't need to compute the intersection point or normal. You're simply checking whether an intersection occurs by solving the quadratic equation and checking the resulting values of t0 and t1.
bool sphere::intersectP(const ray &currentRay) const
{
    ray transformedRay;// = worldToObject->operator*(currentRay);

    
    transformedRay.lookAt = normalize(MathOperations::matrixVector( worldToObject->mt, currentRay.lookAt,  0));
    
    transformedRay.lookFrom = (MathOperations::matrixVector(worldToObject->mt, currentRay.lookFrom,  1));

    float t0 = 0;
    float t1 = 0;

    //point3<float> transformedCenter = center;
    point3<float> transformedCenter = (MathOperations::matrixVector(worldToObject->mt, center,  0));

    vector3<float> L = transformedRay.lookFrom - transformedCenter;

    float a = transformedRay.lookAt * transformedRay.lookAt;
    float b = 2 * (transformedRay.lookAt * L);
    float c = (L * L) - (radius * radius);

    if (!math.solveQuadratic(a, b, c, t0, t1)) {
        return false;
    }
    if (t0 > t1) std::swap(t0, t1);
    if (t0 < 0) {
        t0 = t1;

        if (t0 < 0)
            return false;
    }

    return true;
}


std::shared_ptr<Shapes> createSphereShape(const transformation *o2w,
                                         const transformation *w2o,
                                         const objParamMap &params) {

     int curMaterial;
    
    float radius = params.findOneFloat("radius", 999.f) ;
    vector3<float> center = params.findOneVector3F("position", vector3<float>()) ;
    //const Material *material = params.findMaterial("material",  &curMaterial);

    
    //Float zmin = params.FindOneFloat("zmin", -radius);
    //Float zmax = params.FindOneFloat("zmax", radius);
    //Float phimax = params.FindOneFloat("phimax", 360.f);
    
    
    /*
    //this should be gotten rid of but just trying to get it working now
    std::shared_ptr<transformation> sharedO2W = std::make_shared<transformation>(*o2w);
    std::shared_ptr<transformation> sharedW2O = std::make_shared<transformation>(*w2o);
*/
    
    return std::make_shared<sphere>(o2w, w2o, radius, center);
}
