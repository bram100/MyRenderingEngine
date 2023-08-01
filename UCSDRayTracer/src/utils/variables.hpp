//
//  variables.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#ifndef variables_hpp
#define variables_hpp

#include <stdio.h>
#include "vector.hpp"
#include "sample.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "normal.hpp"
#include "intersection.hpp"
#include "transform.hpp"

#include "testing.hpp"

class intersection;
//class transformation;

#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN float w, h;
EXTERN int maxDepth;
EXTERN float aspectRatio;


EXTERN int maxVertArraySize;
EXTERN int nTriangles;

EXTERN ray currentRay;
EXTERN sample2 currentSample;
EXTERN vector3<float> currentDirection;
EXTERN int currentObjectIndex;

EXTERN ray tranformedRay;
EXTERN std::ofstream outdata;

EXTERN point3<float> localGeoPos;
EXTERN normal<float> localGeoNormal;


EXTERN float tHit;
EXTERN intersection intersct; 

#endif /* variables_hpp */


