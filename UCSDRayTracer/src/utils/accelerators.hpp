//
//  accelerators.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 7/5/23.
//

#ifndef accelerators_hpp
#define accelerators_hpp

#include <stdio.h>

#include "point.hpp"
#include "primitive.hpp"

class boundingBox3F {
public:
    boundingBox3F() {
    // Initialize the bounding box to an invalid state
    min = point3<float>(-std::numeric_limits<float>::infinity());
    max = point3<float>(-std::numeric_limits<float>::infinity());
  }

    boundingBox3F(const point3<float>& min, const point3<float>& max)
    : min(min), max(max) {}

  void ExpandBy(const point3<float>& point) {
    min = point3<float>(std::min(min.x, point.x), std::min(min.y, point.y), std::min(min.z, point.z));
    max = point3<float>(std::max(max.x, point.x), std::max(max.y, point.y), std::max(max.z, point.z));
  }

  // Add other methods as needed

private:
    point3<float> min; // Minimum coordinates of the bounding box
    point3<float> max;
    // Maximum coordinates of the bounding box
};


class Accelerator {
public:
    std::shared_ptr<primitive> MakeAccelerator(
        const std::string& name, std::vector<std::shared_ptr<primitive>> prims, const objParamMap& paramSet);
};

class BVH : public Accelerator {
public:
    BVH(std::vector<std::shared_ptr<primitive>> prims, const objParamMap& paramSet);

private:
    void createBVHAccelerator(std::vector<std::shared_ptr<primitive>> prims, const objParamMap& paramSet);
};





#endif /* accelerators_hpp */
