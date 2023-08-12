//
//  camera.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 1/21/23.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "variables.hpp"
#include "scene.hpp"
#include "ray.hpp"
#include <cmath>

/*
 Note that fov stands for the field of view in the y direction. The field of view in the x direction will be determined by the image size. The world aspect ratio (distinct from the width and height that determine image aspect ratio) is always 1
 */
class Camera {
public:
    
    
    vector3<float> cameraPosition;
    vector3<float> cameraLookAt;
    vector3<float> cameraUp;
    float fov;

    vector3<float> lower_left_corner;
    vector3<float> horizontal;
    vector3<float> vertical;
    float aspectRatio;
    float nearClip;
    float farClip;
    
    transformation cameraViewTransformation;
    matrix4& worldToCamera = cameraViewTransformation.mt;
    matrix4& cameraToWorld = cameraViewTransformation.minvt;
    matrix4 perspectiveMatrix;

//no idea why thisexists 
    transformation cameraShapeTransformation;// = *objectToWorld ^ worldToCamera;


    Camera() :  cameraPosition(vector3<float>(0.0f, 0.0f, 0.0f)),
                cameraLookAt(vector3<float>(0.0f, 0.0f, 1.0f)),
                cameraUp(vector3<float>(0.0f, 1.0f, 0.0f)),
                fov(45.0f), //fov in the y direction
                aspectRatio(1.f),
                nearClip(0.f),
                farClip(infinity)/*,
                cameraToWorld(matrix4())*/{
                  //updateCameraParameters();
              }

    Camera(const vector3<float>& cameraPosition, const vector3<float>& cameraLookAt, const vector3<float>& cameraUp, float fov, float aspect_ratio, float nearClip, float farClip, matrix4 cameraToWorld)
    : cameraPosition(cameraPosition), cameraLookAt(cameraLookAt), cameraUp(cameraUp), fov(fov), nearClip(nearClip), farClip(farClip), aspectRatio(aspectRatio)/*, cameraToWorld(cameraToWorld) */{
        updateCameraParameters();
        
    }

    void updateCameraParameters() {
        
        lookat(cameraPosition, cameraLookAt, cameraUp, cameraViewTransformation);
        
        createPerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
            
        }
    
    

    void generateRay(const sample2& currentSample, ray* currentRay){
        
        ray tempRay;
        float scale = tan(fov * 0.5f * M_PI / 180.0f);

        float pixelX = (2.0f * (currentSample.x + 0.5f) / w - 1.0f) * aspectRatio * scale;
        float pixelY = (1.0f - 2.0f * (currentSample.y + 0.5f) / h) * scale;
        
        tempRay.lookAt = vector3<float>(pixelX, pixelY, -1.0f);
        //tempRay.lookAt = worldToCamera * normalize(tempRay.lookAt) /* * cameraViewTransformation.mt */;
        
        tempRay.lookAt = normalize(MathOperations::matrixVector(worldToCamera, tempRay.lookAt, 0.0f));

        tempRay.lookFrom = cameraPosition /** cameraViewTransformation.mt*/;
        



        tempRay.t_max = infinity;
        tempRay.t_min = infinity * -1;
        
        

        
        
        //this is bad code
       // tempRay.lookFrom = perspectiveMatrix * tempRay.lookFrom;

        currentRay->lookAt = tempRay.lookAt;
        currentRay->lookFrom = tempRay.lookFrom;

        
        }
    
    void lookat(const vector3<float>& from, const vector3<float>& to, const vector3<float>& up, transformation& m)
    {
     
        vector3<float> dir = normalize(from - to);
        vector3<float> right = normalize((normalize(up))^dir);
        vector3<float> newUp = (dir ^ right);
             m.mt[0][0] = right.x;
             m.mt[1][0] = right.y;
             m.mt[2][0] = right.z;
             m.mt[3][0] = 0.;
             m.mt[0][1] = newUp.x;
             m.mt[1][1] = newUp.y;
             m.mt[2][1] = newUp.z;
             m.mt[3][1] = 0.;
             m.mt[0][2] = dir.x;
             m.mt[1][2] = dir.y;
             m.mt[2][2] = dir.z;
             m.mt[3][2] = 0.;
        
        m.updateInverse();
    }
    
    void createPerspectiveMatrix(float fov, float aspectRatio, float nearClip, float farClip) {

        float tanHalfFOV = tanf(fov / 2.0f);
        float zRange = nearClip - farClip;

        perspectiveMatrix.m[0][0] = 1.0f / (aspectRatio * tanHalfFOV);
        perspectiveMatrix.m[1][1] = 1.0f / tanHalfFOV;
        perspectiveMatrix.m[2][2] = (nearClip + farClip) / zRange;
        perspectiveMatrix.m[2][3] = 2.0f * farClip * nearClip / zRange;
        perspectiveMatrix.m[3][2] = -1.0f;

        return perspectiveMatrix;
    }


};

#endif /* camera_hpp */
