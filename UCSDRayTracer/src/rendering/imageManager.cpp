//
//  imageManager.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/12/23.
//
#include <iostream>
#include <fstream>

#include "imageManager.hpp"
#include <string>
#include <strstream>


bool readValuesInt(std::string& command, const int numvals, int values[10], int lenght) {
    int f;
    std::stringstream stringStream (command);   /* make stringstream from s */
    for (int i = 0; i < numvals; i++) {
        stringStream >> f;
        values[i] = f;
    }
}

bool readValuesFloat(std::string& command, const int numvals, float valuesf[10], int lenght) {
    
    float f;
    std::stringstream stringStream (command);   /* make stringstream from s */
    
    for (int i = 0; i < numvals; i++) {
        stringStream >> f;
        valuesf[i] = f;
    }
}

      
void printTest(const int numvals, int values[10]) {
    for (int i = 0; i < numvals; i++) {
        std::cout<< values[i] << std::endl;
    }
}


void createBlankImage (std::ofstream& outdata, int image_width, int image_height) {
    outdata << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
}



