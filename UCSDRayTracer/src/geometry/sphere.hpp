//
//  sphere.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 4/9/23.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>
#include "shape.hpp"
#include "material.hpp"

class sphere : public Shapes {
  public:
    // Sphere Public Methods
    sphere(const transformation *o2w, const transformation *w2o, float radius, vector3<float> center) : Shapes(o2w, w2o), radius(radius), center(center) {
        
        //this->material = std::make_unique<Material>(material);
        
    }
    //bool intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const;
    
    //why override????
    bool intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const override;
    
    //why overrride
    bool intersectP(const ray &ray) const override;

    //bool intersectp(const Ray &ray, bool testAlphaTexture) const;
    //Float Area() const;
    //Interaction Sample(const Point2f &u, Float *pdf) const;
    //Interaction Sample(const Interaction &ref, const Point2f &u, float *pdf) const;
    //Float Pdf(const Interaction &ref, const Vector3f &wi) const;
    //Float SolidAngle(const Point3f &p, int nSamples) const;

  private:
    // Sphere Private Data
    const float radius;
    const vector3<float> center;
    //std::unique_ptr<Material> material;
    //const Float zMin, zMax;
    //const Float thetaMin, thetaMax, phiMax;
};

std::shared_ptr<Shapes> createSphereShape( const transformation *o2w,  const transformation *w2o, const objParamMap &params);



#endif /* sphere_hpp */
