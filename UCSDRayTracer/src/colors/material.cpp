//
//  material.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#include "material.hpp"

void getBRDF(localGeo& local, BRDF* brdf) {
    
}


/*
I = A + E + ∑ ( 𝑉 * (L / (c0 + c1 * r + c2 * r^2))) * (D max(N • L, 0) + S max (N • H, 0)^s)

I = color3 intensity
A = color3 ambient
E = color3 emission
V = bool //vissible
c0 c1 c2 = attenuation (applies only to point lights, not directional lights)
r r^2
L = vector3(?) directionToLight
D = color3 diffuse
S = color3 specular
N = normal surfaceNormal

*/
