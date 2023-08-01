//
//  vector.cpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/4/23.
//

#include "point.hpp"
#include "vector.hpp"

template <typename T>
vector3<T>::operator point3<float>*() const {
    return new point3<float>(x, y, z);
}

