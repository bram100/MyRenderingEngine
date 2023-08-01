//
//  texture.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 7/19/23.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>

template <typename T>
class Texture {
public:
    // Constructor
    Texture() {}

    // Overloaded constructor to set the initial value
    explicit Texture(const T& value) : value_(value) {}

    // Function to get the value of the texture at a specific point
    T Evaluate(/* Parameters for texture evaluation, e.g., coordinates */) const {
        // Implementation of texture evaluation based on the input parameters
        // ...
        // For simplicity, let's return the stored value in this example.
        return value_;
    }

private:
    T value_;
};

#endif /* texture_hpp */
