//
//  primitive.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/19/23.
//


/*
Primitive to compute the nearest ray-object intersection

primitive must call geometricPrimitive to compute ray-object intersection
 
Primitive will transform the ray from world space to object space and hand it to Shape to do intersection in object space.

Then it shades that pixel returns the resulting color to scene.
 
 Shape then computes the intersection and returns the result to Primitive.

*/

/*

 //Primitive will transform the ray from world space to object space and hand it to Shape to do intersection in object space

//primative will call intersect

//Primitive base class is the bridge between the geometry processing and shading



/*
    //transformation<float> objToWorld, worldToObj;
    //shape* shape;
    //material* mat;
    //matrix4 tempMat;
    //primitive(){};
    //shape shape;

    //intersection take the geoCoord(position and the normal
    
    
    
    
    //virtual bool intersect(ray& currentRay, float* tHit);//, intersection inter);
    
    virtual void intersect();


    
    virtual bool intersectP(ray& currentRay);
    
    //void getBRDF(LocalGeo& local, BRDF* brdf);
    //void getcolor(localGeo& local, color3 brdf);
    
    
};


*/
/*
#ifndef primitive_hpp
#define primitive_hpp

#include <stdio.h>
//#include "variables.hpp"
//#include "ray.hpp"
class ray;
class shape;
class intersection;
#include "shape.hpp"
#include "intersection.hpp"
//#include "intersection.hpp"
//#include "variables.hpp"

//#include "localGeo.hpp"

/*
#include "variables.hpp"
*/

//class intersection;
/*
class primitive {
public:
    //virtual ~primitive();
    
    
    typedef int currentPrimitive; // declare a type name BaseInt for int
    currentPrimitive baseIntVar;
    
    virtual bool intersect(ray& ray, float* tHit, intersection* intersct);
    
//private;
    /*
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Material> material;
    std::shared_ptr<AreaLight> areaLight;
    MediumInterface mediumInterface;
*/
    //shape shape;

    /*
     ABTRACT CLAS!!!!!!!!!!!!
     
};

#endif
*/


#ifndef primitive_hpp
#define primitive_hpp

#include "ray.hpp"
//#include "intersection.hpp"
//#include "material.hpp"
#include "shape.hpp"

class intersection;
class Material;
class BRDF;
class Shapes;
class primitive {
public:
    
   // primitive(const std::shared_ptr<Shapes>& shape, const std::shared_ptr<Material>& material) : shape(shape), material(material) {}
    virtual std::string getShapeType() const = 0;

    virtual bool intersect(ray& ray, float* thit, intersection* intersct) = 0;
    virtual bool intersectP(ray& ray) = 0;

    //virtual bool intersectP(ray& ray) = 0;
    virtual void getBRDF(localGeo& local, BRDF* brdf) = 0;
    
    
    virtual std::shared_ptr<Material> getMaterial() const = 0;

private:
    //std::shared_ptr<Shapes> shape;
   // std::shared_ptr<Material> material;

};

#endif

