//
//  sampler.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/24/23.
//

#include "sampler.hpp"
#include "readCommand.hpp"
#include "sample.hpp"

sampler::sampler(int width, int height) : width(width), height(height), currentX(0), currentY(0) {}

bool sampler::getSample(sample2* currentSample) {

    if (currentY == height) {
        return true;
    }
    currentSample->x = currentX;
    currentSample->y = currentY;
    currentX++;

    if (currentX == width) {
        currentX = 0;
        currentY++;

    }

    return false;
}


