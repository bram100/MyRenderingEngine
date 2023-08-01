//
//  color.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/25/23.
//

#include "color.hpp"

color3 convertFloatToColor(const float floatValues[10]) {
    
int r = static_cast<int>(floatValues[0] * 255);
int g = static_cast<int>(floatValues[1] * 255);
int b = static_cast<int>(floatValues[2] * 255);

return color3(r, g, b);
}
