//
//  scene.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include "ray.hpp"
#include "localGeo.hpp"
#include "color.hpp"
//#include "camera.hpp"
#include "primitive.hpp"
#include "geometricPrimitive.hpp"
#include "vector.hpp"


class Scene {
public:
    void addGeometricPrimitive(std::shared_ptr<GeometricPrimitive> geometricPrimitive);
    
    

    void renderer();
    

//private: why was this private?
    std::vector<std::shared_ptr<GeometricPrimitive>> geometricPrimitives;
  //std::vector<std::shared_ptr<TransformedPrimitive>> transformedPrimitives;
    
    transformationSet transformationStack;

    int frameNumber; //defined as seconds * fps
};



#endif /* scene_hpp */
