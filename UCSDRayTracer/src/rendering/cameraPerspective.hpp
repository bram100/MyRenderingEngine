//
//  cameraePerspective.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 6/29/23.
//

#ifndef cameraPerspective_hpp
#define cameraPerspective_hpp

#include <stdio.h>

#include <stdio.h>
#include "matrix.hpp"
#include <cmath>

//this doesnt do anything right now


void setProjectionMatrix(const float &angleOfView, const float &near, const float &far, matrix4 &M)
{
    // set the basic projection matrix
    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
    M[0][0] = scale;  //scale the x coordinates of the projected point
    M[1][1] = scale;  //scale the y coordinates of the projected point
    M[2][2] = -far / (far - near);  //used to remap z to [0,1]
    M[3][2] = -far * near / (far - near);  //used to remap z [0,1]
    M[2][3] = -1;  //set w = -z
    M[3][3] = 0;
}
void multPointMatrix(const vector3<float> &in, vector3<float> &out, const matrix4 &M)
{
    //out = in * M;
    out.x   = in.x * M[0][0] + in.y * M[1][0] + in.z * M[2][0] + /* in.z = 1 */ M[3][0];
    out.y   = in.x * M[0][1] + in.y * M[1][1] + in.z * M[2][1] + /* in.z = 1 */ M[3][1];
    out.z   = in.x * M[0][2] + in.y * M[1][2] + in.z * M[2][2] + /* in.z = 1 */ M[3][2];
    float w = in.x * M[0][3] + in.y * M[1][3] + in.z * M[2][3] + /* in.z = 1 */ M[3][3];
 
    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }
}


#endif /* cameraPerspective_hpp */
