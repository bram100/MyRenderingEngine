//
//  imageManager.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/12/23.
//
#ifndef imageManager_hpp
#define imageManager_hpp

#include <iostream>
#include <sstream>

using std::cerr;
using std::endl;
using std::ofstream;

bool readValuesInt(std::string& command, const int numvals, int valuesi[10], int lenght);

bool readValuesFloat(std::string& command, const int numvals, float valuesf[10], int lenght);

void printTest(const int numvals, int values[10]);

void createBlankImage(std::ofstream& outdata, int image_width, int image_height);

#endif /* imageManager_hpp */
