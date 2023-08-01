//
//  variables.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#include "variables.hpp"
#include <fstream>
 
//objects
int maxVertArraySize; //nVertices
int nTriangles;

//keep track of current ray
ray currentRay;
sample2 currentSample;
vector3<float> currentDirection;
int currentObjectIndex;

ray tranformedRay;
std::ofstream outdata;

//maybe ill be able to replace with localgeo file?
point3<float> localGeoPos;
normal<float> localGeoNormal;


float tHit; //If an intersection is found, its parametric distance along th222e ray should be stored in the tHit



