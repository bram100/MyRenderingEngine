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


void commit(sample2 sample, color3 color) {
    //std::cout << color << std::endl;
    outdata << color << std::endl;
}
