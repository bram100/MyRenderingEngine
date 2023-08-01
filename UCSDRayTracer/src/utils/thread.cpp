//
//  thread.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 6/17/23.
//

#include "thread.hpp"
#include <iostream>
#include <chrono>
//#include "camera.hpp"

/*
VariableChecker::VariableChecker(Camera& camera) : myCamera(camera)
{
    checkThread = std::thread(&VariableChecker::CheckVariable, this);
}

VariableChecker::~VariableChecker()
{
    // Wait for the check thread to finish
    if (checkThread.joinable()) {
        checkThread.join();
    }
}

void VariableChecker::CheckVariable()
{
    while (true)
    {
        
        Camera previousCamera = myCamera; // Store the previous state of the Camera object
        std::cout << myCamera.cameraPosition << std::endl;
        // Check if any of the Camera member variables have changed
        // Example: Checking if cameraPosition has changed
        if (myCamera.cameraPosition != previousCamera.cameraPosition)
        {
            std::cout << "cameraPosition has changed: " << myCamera.cameraPosition << std::endl;
            // Update the previous value to the current value
            // Example: previous cameraPosition = myCamera.cameraPosition
        }

        // Repeat the above for other Camera member variables (e.g., cameraLookAt, cameraUp, fov)

        // Sleep for a while to avoid constant checking
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
*/




/*
int main(int argc, char **argv)
{
    int imageWidth = 512, imageHeight = 512;
    matrix4 Mproj;
    matrix4 worldToCamera;
    worldToCamera[3][1] = -10; //idk
    worldToCamera[3][2] = -20; //idk
    float angleOfView = 90;
    float near = 0.1;
    float far = 100;
    //setProjectionMatrix(angleOfView, near, far, Mproj);
    unsigned char *buffer = new unsigned char[imageWidth * imageHeight];
    memset(buffer, 0x0, imageWidth * imageHeight);
    for (uint32_t i = 0; i < numVertices; ++i) {
        Vec3f vertCamera, projectedVert;
        worldToCamera = vertices[i] * vertCamera; //point matrix multiplcation return a matrix
        mProj = vertCamera * projectedVert; //point matrix
        if (projectedVert.x < -1 || projectedVert.x > 1 || projectedVert.y < -1 || projectedVert.y > 1) continue;
        // convert to raster space and mark the position of the vertex in the image with a simple dot
        uint32_t x = std::min(imageWidth - 1, (uint32_t)((projectedVert.x + 1) * 0.5 * imageWidth));
        uint32_t y = std::min(imageHeight - 1, (uint32_t)((1 - (projectedVert.y + 1) * 0.5) * imageHeight));
        buffer[y * imageWidth + x] = 255;
    }

*/

/*
void render(
    const Options &options,
    const std::vector<std::unique_ptr<Object>> &objects,
    const std::vector<std::unique_ptr<Light>> &lights)
{
    extern matrix4 cameraToWorld;
    vector3<float> *framebuffer = new vector3<float>[options.width * options.height];
    vector3<float> *pix = framebuffer;
    float scale = tan(deg2rad(options.fov * 0.5));
    float imageAspectRatio = options.width / (float)options.height;
    vector3<float> orig;
    orig = (vector3<float>(0.f, 0.f, 0.f) * cameraToWorld); //vec matrix multiplcation
    for (uint32_t j = 0; j < options.height; ++j) {
        for (uint32_t i = 0; i < options.width; ++i) {
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
            vector3<float> dir;
            dir = vector3<float>(x, y, -1) * cameraToWorld; //of ray direction
            normalize(dir);
            *(pix++) = castRay(orig, dir, objects, lights, options, 0);
        }
    }


    vector3<float> origCameraSpace = orig * cameraToWorld; //Transform origin from world space to camera space
    
    vector3<float> dirCameraSpace = dir * cameraToWorld; // Transform direction from world space to camera space
    
    vector3<float> dirCameraSpaceNoramlized = normalize (dirCameraSpace);

    *(pix++) = castRay(origCameraSpace, dirCameraSpace, objects, lights, options, 0);
*/

/*
int main(int argc, char **argv)
{
    vector3f v0(-1, -1, -5);
    vector3f v1( 1, -1, -5);
    vector3f v2( 0,  1, -5);
    
    const uint32_t width = 640;
    const uint32_t height = 480;
    Vec3f cols[3] = {{0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7}};
    Vec3f *framebuffer = new Vec3f[width * height];
    Vec3f *pix = framebuffer;
    float fov = 51.52;
    float scale = tan(deg2rad(fov * 0.5));
    float imageAspectRatio = width / (float)height;
    Vec3f orig(0);
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            // compute primary ray
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            Vec3f dir(x, y, -1);
            //cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
            dir.normalize();
            float t, u, v;
            if (rayTriangleIntersect(orig, dir, v0, v1, v2, t, u, v)) {
                *pix = u * cols[0] + v * cols[1] + (1 - u - v) * cols[2];
                //*pix = Vec3f(u, v, 1 - u - v);
            }
            pix++;
        }
    }
*/
