//
//  geometricPrimitive.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/27/23.
//

#ifndef geometricPrimitive_hpp
#define geometricPrimitive_hpp

#include <stdio.h>
#include "primitive.hpp"

#include "ray.hpp"
#include "matrix.hpp" //maybe?
#include "shape.hpp"
#include "intersection.hpp"
//#include "material.hpp"

#include "accelerators.hpp"


//
class GeometricPrimitive : public primitive {
public:
    GeometricPrimitive(const std::shared_ptr<Shapes>& shape, const std::shared_ptr<Material>& material)
        : shape(shape), material(material) {}

    transformation objToWorld, worldToObj;
    //geometricPrimitive(const std::shared_ptr<Shapes> &shape);
    
    virtual bool intersect(ray& ray, float* tHit, intersection* intersct) override ;

    virtual bool intersectP(ray& ray) override ;

    void getBRDF(localGeo& local, BRDF* brdf) override;

    std::shared_ptr<Material> getMaterial() const override {
        return material;
    }

    boundingBox3F WorldBound() const {
      // Compute the world-space bounding box of the shape
      //return shape->WorldBound();
    }
    

    /*
     void applyTransformationToObject( const transformation& other) {
        
     shape->multiplyObjectToWorld(other);
    }
*/
    //void applyTransformationToWorld( transformation& other) { shape->multiplyWorldToObject(other); }


    


private:
    std::shared_ptr<Shapes> shape;
    std::shared_ptr<Material> material;
};

#endif


