//
//  material.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/3/23.
//

#include "material.hpp"
#include "ray.hpp"
#include "math.hpp"
#include "vector.hpp"
#include "camera.hpp"

#include <cmath> //pow
extern Camera camera;

void getBRDF(localGeo& local, BRDF* brdf) {
    
}
vector3<float> const testing;
vector3<float> const testing2;


color3 Material::shading(const localGeo& intersection, const ray& lightRay, const color3& lightColor){
        
    color3 finalColor;
    
    finalColor += ambient;
    
    finalColor += aBRDF.emission;
    //finalColor += emissionComponent;
    
    return finalColor;

    /*
    float cosTheta = dot(intersection.normal, lightRay.direction);

    // Apply Lambertian reflection model for diffuse reflection
    color3 diffuseComponent = aBRDF.diffuse * lightColor * max(cosTheta, 0.0f);

    // Combine the diffuse component with ambient term
    color3 ambientDiffuse = brdf.ambient + diffuseComponent;

    // Final shading color with BRDF components
    color3 finalColor = ambientDiffuse;

*/
    //bool V
    
   

    

    //std::cout << ambient << std::endl;
    return finalColor;

    
}


color3 Material::shadingShadows(const localGeo& intersection, const ray& lightRay, const color3& lightColor){
    
    //vector3<int> attenuation(0,0,0);
    color3 finalColor;
    
    auto normalizeLight =  normalize(lightRay.lookAt);

    auto normalizeNormal = normalize(intersection.normal);
  

    float cosTheta = MathOperations::dotProduct(normalizeNormal, normalizeLight); //dot product

    color3 diffuseComponent = aBRDF.diffuse * lightColor * fmax(cosTheta, 0.0f);
    
    finalColor += diffuseComponent;

    //'vector3 viewerDirection = normalize(cameraPosition - surfacePoint);
    
    //Shading is almost like in previous homeworks, except attenuation for point light source and eyepos which was previously zero. Initially variable eyepos equals to camera position, after re- flection it should be point of reflection. So, eyepos is ray start point.
    
    //halfEdge == halfAngle???
    
   // "H" is the normalized half-vector between the direction of the viewer's eye (or camera) and the direction of the light source. It is often used to approximate the direction in which light is being reflected from the surface.
    
    //calcualte half-edge (view direction + light direction)
    vector3 viewDirection = normalize(camera.cameraPosition - intersection.pos);
    vector3 halfEdge = normalize(viewDirection + lightRay.lookAt);

    
    //dot product of normalized surface normal and normalizd half vector
    float dotProduct = MathOperations::dotProduct(normalizeNormal, halfEdge);
    
    
    float cosine = MathOperations::cosineAngle(lightRay.lookAt, viewDirection);

    //(max of dot product, 0)^ shineness
    //float shineness = std::pow(fmax(dotProduct, 0.f), std::pow(cosine,  aBRDF.shininess));
    
    
    //o think here
    float shineness = std::pow(fmax(dotProduct, 0.f),  aBRDF.shininess);

    
    color3 specularComponent = aBRDF.specular * shineness;
    
    
 
    
   // color3 specularComponent = aBRDF.specular * pow(fmax(normalizeNormal, halfEdge), aBRDF.shininess );

    

    //specular * max(dot product(normalized surface normal, normalized half-vector), 0) ^ power shininess
    finalColor += specularComponent;

    
    
  //  L / c0 + c1 * r + c2 * r^2
    /*
    c0, c1, c2 are the constant, linear and quadratic attenuation terms, while r is the distance to the light. Physical point lights have (c0, c1, c2) = (0, 0, 1) while the default (no attenuation) is (c0, c1, c2) = (1, 0, 0).
    */
    
    return  finalColor;

    
    
   // finalColor += diffuseComponent;

    
}
/*
if light == point
    cVector = (0, 0, 1)


//cvector is const, linear and quadtratic attenuation
lightRay.lookAt / (cVector.x + xVector.y * r + cVector.z * std::pow(r))

/*
 A and E are added regardless of light
 
sum over all lights
    if vissible V
        L / attenuation
            * diffuse
                * specular
        

 sum (attenuation * (surfaceNormal + specular))
I = A + E + ∑  𝑉 * (L / (c0 + c1 * r + c2 * r^2))) * ((D max(N • L, 0) + S max (N • H, 0)^s) + SIr

I = color3 intensity
A = color3 ambient
E = color3 emission
V = bool //vissible (ok, this value neends something)
c0 c1 c2 = attenuation (applies only to point lights, not directional lights)
r r^2
L = vector3(?) directionToLight
D = color3 diffuse
S = color3 specular
N = normal surfaceNormal
H = the half-angle (what????)
 
 
 
 
 I = KˇA + KˇE + ∑  𝑉ˇi * L^i  ((K max(L • N, 0) + K max (H • N, 0)^s) + KIr

*/
