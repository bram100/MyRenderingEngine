//
//  material.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#include "material.hpp"
#include "ray.hpp"
#include "math.hpp"

void getBRDF(localGeo& local, BRDF* brdf) {
    
}

color3 Material::shading(const localGeo& intersection, const ray& lightRay, const color3& lightColor){
    
    //ok, i am passing in intersectoin. Interseciton contains pos and normal
    
    color3 finalColor;
    
    finalColor += aBRDF.diffuse;

    
    float cosTheta = MathOperations::dotProduct(intersection.normal, lightRay.lookAt); //dot product
    
    //std::cout << cosTheta << std::endl;
    
    /*
    if (cosTheta <= 0.0f) {
        return color3(0.0f, 0.0f, 0.0f); // No diffuse reflection on the back side of the surface
    }
*/
   // finalColor +=  aBRDF.diffuse;// * lightColor * cosTheta;
    color3 diffuseComponent = aBRDF.diffuse * lightColor * fmax(cosTheta, 0.0f);

    //finalColor += diffuseComponent;
    
    
    /*
    float cosTheta = dot(intersection.normal, lightRay.direction);

    // Apply Lambertian reflection model for diffuse reflection
    color3 diffuseComponent = aBRDF.diffuse * lightColor * max(cosTheta, 0.0f);

    // Combine the diffuse component with ambient term
    color3 ambientDiffuse = brdf.ambient + diffuseComponent;

    // Final shading color with BRDF components
    color3 finalColor = ambientDiffuse;

*/
    
    
   

    

    //std::cout << ambient << std::endl;
    return finalColor;

    
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
