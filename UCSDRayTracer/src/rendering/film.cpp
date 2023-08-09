//
//  film.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/25/23.
//

#include "film.hpp"
#include "color.hpp"
#include <iostream>
#include <fstream>

/*
void commit(sample2 sample, color3 color) {
   // std::cout << "Color: (" << color->r << ", " << color->g << ", " << color->b << ")" << std::endl;

    outdata << color << std::endl;
    //outdata << "Color: (" << color->r << ", " << color->g << ", " << color->b << ")" << std::endl;

    //color->r = 0;
    //color->g = 0;
    //color->b = 0;
    
    
}
*/

void commit(sample2 sample, color3* color) {
    
    //std::cout << "Color: (" << color->r << ", " << color->g << ", " << color->b << ")" << std::endl;

    
    outdata << color->r << " " << color->g << " " << color->b << std::endl;
    
    color->r = 0;
    color->g = 0;
    color->b = 0;
    
}
