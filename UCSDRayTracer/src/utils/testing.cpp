//
//  testing.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/22/23.
//
/*
#include "testing.hpp"
#include <thread>
#include "thread.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>

#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

#include "imageManager.hpp"
#include "readCommand.hpp"
#include "CImg.h"
#include "scene.hpp"

#include "brdf.hpp"
#include "material.hpp"

#include "primitive.hpp"
#include "geometricPrimitive.hpp"
//#include "camera.hpp"
#include "scene.hpp"
using namespace std;
using namespace cimg_library;

//is it proper to init these variables here?
std::string imageNamePPM = "doggo2.ppm";
std::shared_ptr<Shapes> aShape;
std::vector<vector3<int>> triArray;
std::vector<point3<float>> vertexPointArray;

Camera camera;
objParamMap params;
Scene scene;

std::shared_ptr<Material> materialParsed = std::make_shared<Material>();
int countingj = 0;



float w, h;
int maxDepth;
int newI;

std::vector<std::shared_ptr<Shapes>> shapesContainer;
std::vector<std::shared_ptr<GeometricPrimitive>> prims;


transformation tranform;

transformationSet curTransform;
static transformCache transformCache;

void output2(std::ofstream& outdata)
{
    outdata << "does this work?" << endl;
}

void readfile(const char* fileName)
{
    //std::atomic<int> myVariable(0); // Variable to be checked
    //std::thread checkThread(camera);

   // VariableChecker variableChecker(camera);
    
    string str, cmd;
    ifstream fileIn;
    
    fileIn.open(fileName);
    
    if (fileIn.is_open())
      {
        std::cout << "File loaded successfully\n";
      }
      else
      {
        std::cout << "Error opening file";
        //https://stackoverflow.com/questions/23438393/new-to-xcode-cant-open-files-in-c
      }
    int myCounting = 0;

    
    if (fileIn.is_open()) {
        getline (fileIn, str);

        while (fileIn) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                
                
                stringstream s(str);
                s >> cmd;
                int i;
                int valuesi[10];
                float valuesf[10];
                bool validinput; // Validity of input
                
                // Process the light, add it to database.
                // Lighting Command
                
                
                if (cmd == "fileName") {
                    str.erase(0, 9);
                    outdata.open(str);
                    if( !outdata ) { // file couldn't be opened
                       cerr << "Error: file could not be opened" << endl;
                       exit(1);
                    }
                    
                    imageNamePPM = str;
                    std::cout << "\nimage saved: " << str <<  "\n\n";
                }
                
                if (cmd == "resolution" || cmd == "size") {
                    str.erase(0, 10);
                    readValuesFloat(str, 2, valuesf, 3);
                    w = valuesf[0];
                    h = valuesf[1];
                    camera.aspectRatio = w / h;
                    
                    //camera.aspectRatio = aspectRatio;
                    std::cout << "Resolution Set to: X:" << w << " Y:" << h << std::endl;
                }
               
                if (cmd == "maxdepth") {
                    str.erase(0, 8);
                    readValuesInt(str, 1, valuesi, 3);
                    maxDepth = valuesi[0];
                    std::cout << "max depth set: " << maxDepth << std::endl;
                }
                
                //light  defintions: //this stuff is addded to ray
                if (cmd == "directional") { // x y z r g b
                    str.erase(0, 11);
                    readValuesFloat(str, 6, valuesf, 3);

                }
                
                if (cmd == "point") { //x y z r g b The location of a point source and the color, as in OpenGL.
                    str.erase(0, 5);
                    readValuesFloat(str, 6, valuesf, 3);
                

                }
                
                if (cmd == "attenuation") { //const linear quadratic (Sets the constant, linear and quadratic attenuations (default 1,0,0) as in OpenGL. By default there is no attenuation (the constant term is 1, linear and quadratic are 0; that's what we mean by 1,0,0).
                    str.erase(0, 11);
                    readValuesFloat(str, 3, valuesf, 3);

                }
                
                
                if (cmd == "ambient") { //default is .2,.2,.2
                    str.erase(0, 7);
                    readValuesFloat(str, 3, valuesf, 3);
                    color3 ambientColor = convertFloatToColor(valuesf);

                    //color3 ambientColor(valuesf[0], valuesf[1], valuesf[2]);
                    
                    materialParsed->aBRDF.ambient = ambientColor;
                    
                }

                
                //Note also that if no ambient color or attenuation is specified, you should use the defaults. Note that we allow the ambient value to be changed between objects (so different objects will be rendered with a different ambient term; this is used frequently in the examples).  Finally, note that here and in the materials below, we do not include the alpha term in the color specification.
                
                //materials
                if (cmd == "diffuse") { //r g b
                    str.erase(0, 7);
                    readValuesFloat(str, 4, valuesf, 3);
                    color3 diffuseColor(valuesf[0]*1000, valuesf[1]*1000, valuesf[2]*1000);
                    materialParsed->aBRDF.ambient = diffuseColor;
                }
                if (cmd == "specular") { // r g b
                    str.erase(0, 8);
                    readValuesFloat(str, 4, valuesf, 3);
                    color3 specularColor(valuesf[0]*1000, valuesf[1]*1000, valuesf[2]*1000);
                    materialParsed->aBRDF.specular = specularColor;

                }
                if (cmd == "shininess") { // r g b
                    str.erase(0, 9);
                    readValuesFloat(str, 4, valuesf, 3);
                    color3 shinenessColor(valuesf[0]*1000, valuesf[1]*1000, valuesf[2]*1000);
                    //materialParsed->aBRDF.shineness = shinenessColor;

                }
                if (cmd == "emission") { // r g b
                    str.erase(0, 8);
                    readValuesFloat(str, 4, valuesf, 3);
                    color3 emissionColor(valuesf[0]*1000, valuesf[1]*1000, valuesf[2]*1000);
                   // materialParsed->aBRDF.emission = emissionColor;

                }

                if (cmd == "camera") {
                    str.erase(0, 6);
                    readValuesFloat(str, 10, valuesf, 3);

                    vector3<float> cameraPositionInit(valuesf[0], valuesf[1], valuesf[2]);
                    vector3<float> cameraLookAtInit(valuesf[3], valuesf[4], valuesf[5]);
                    vector3<float> cameraUpInit(valuesf[6], valuesf[7], valuesf[8]);
                    float fovInit = valuesf[9];
                    //scale = tan(fov * 0.5f * M_PI / 180.0f);
                    

                    //camera(cameraPositionInit, cameraLookAtInit, cameraUpInit, fovInit, aspectRatio);

                    
                    
                    camera.cameraPosition = cameraPositionInit;
                    
                    camera.cameraLookAt = cameraLookAtInit;
                    camera.cameraUp = cameraUpInit;
                    camera.fov = fovInit;
                    //cameraToWorld set here
                    camera.updateCameraParameters();
                    
                    /*
                    vector3<float> from(cameraPositionInit);
                    vector3<float> to(cameraLookAtInit);
                    vector3<float> up(cameraUpInit);

                    cameraViewTransformation =transformation (from, to, up);
*/
                    /*
                    std::cout << "camera position " << camera.cameraPosition << std::endl;
                    
                    std::cout << "Camera set: " << std::endl;
                    
                }
                
                if (cmd == "popTransform") {
                    str.erase(0, 12);
                    
                    
                    if (triArray.size() > 0) {
                       string str = "triangleMesh";
                       
                       transformation *o2w = transformCache.lookup(curTransform[0]);
                       transformation *w2o = transformCache.lookup(inverse(curTransform[0]));

                       
                       
                       params.addOneInt("nTriangles", static_cast<int>(triArray.size()));
                       params.addVector3I("triArray", &triArray[0]);
                       params.addOneInt("nVertices", maxVertArraySize);
                       params.addPoint3F("vertexArray", &vertexPointArray[0]);
                                   
                       makeShapes(str, o2w, w2o, params);

                        
                        triArray.clear();
                        triArray.resize(0);

                        //params.clear();
                        

                   }
                    
                   materialParsed = std::shared_ptr<Material>(new Material());

                    newI = 0;

                }
                
                if (cmd == "pushTransform") {
                    str.erase(0, 13);

                }
                
                //sphere centerx centery centerz radius
                if (cmd == "sphere") {
                    
                    str.erase(0, 7);
                    readValuesFloat(str, 10, valuesf, 3);
    
                    //eventually ill need to setup a makTranformation() function
                    
                    //ok, so whats supposed to happen is i create a transformation stack. Then makeShape just calls the most recent transformation stakc, amybe?
                    
                    objParamMap sphereParams;
                    
                    vector3<float> positionArray (valuesf[0], valuesf[1], valuesf[2]);
                    
                   
                    params.addOneVector3F("position", positionArray);
                    params.addOneFloat("radius", valuesf[3]);
                    //lookup will check if curTranform is in the transformCache, if not it will add it to the stack. Then returns a pointer
                    transformation *o2w = transformCache.lookup(curTransform[0]);
                    transformation *w2o = transformCache.lookup(inverse(curTransform[0]));
                    
                   // transformation result = *o2w * cameraViewTransformation;
                    
                    
                    string str = "sphere";
                    makeShapes(str, o2w, w2o, params);
                    countingj++;
                    std::cout << "sphere number  " << countingj << std::endl;
                    
                    shapesContainer.push_back(aShape);
                    

                    //std::cout << "shape number " << shapesContainer.size() << "set as a " << str << std::endl;
                    
                    //sphere.printValues();

                }
                
                if (cmd == "maxverts") {
                    str.erase(0, 8);
                    readValuesInt(str, 2, valuesi, 3);
                    maxVertArraySize = valuesi[0];

                    std::cout << "max verts read: " << maxVertArraySize << std::endl;

                }

                if (cmd == "vertex") {
                    str.erase(0, 6);
                    readValuesFloat(str, 4, valuesf, 3);
                    
                    vertexPointArray.push_back(point3<float> (valuesf[0], valuesf[1], valuesf[2]));
                    
                }
                
                if (cmd == "tri") {
                    str.erase(0, 3);
                    readValuesInt(str, 4, valuesi, 3);
                    
                    transformation *o2w = transformCache.lookup(curTransform[0]);
                    transformation *w2o = transformCache.lookup(inverse(curTransform[0]));

                    
                    //maybe placing these outside function makes it more efficent?

                    triArray.resize(newI+1);

                    triArray[newI] = vector3<int> (valuesi[0], valuesi[1], valuesi[2]);
                    
                    newI++;
                    
                                        
                }

                if (cmd == "maxvertnorms") {
                    str.erase(0, 12);

                }
                
                
                if (cmd == "vertexnormal") {
                    str.erase(0, 8);

                }
                                
                if (cmd == "trinormal") {
                    
                }
                
                
                    //this has to move up
                if (cmd == "translate") {
                    str.erase(0, 10);
                    readValuesFloat(str, 4, valuesf, 3);
                    
                     vector3<float> translateVector(valuesf[0], valuesf[1], valuesf[2]);

                    tranform.translation(translateVector);
                }
                
                if (cmd == "rotate") {
                    str.erase(0, 7);
                    readValuesFloat(str, 4, valuesf, 3);
                    
                    vector3<float> translateVector(valuesf[0], valuesf[1], valuesf[2]);
                    float theta = valuesf[3];

                    
                    transformation rotationMatrix = transformation::rotation(theta, translateVector);
                }
                
                if (cmd == "scale") {
                    str.erase(0, 5);
                    readValuesFloat(str, 4, valuesf, 3);
                    
                     vector3<float> translateVector(valuesf[0], valuesf[1], valuesf[2]);

                    tranform.scaling(translateVector);
                }
                
                
                if (cmd == "end") {
                    goto endParsing;
                }
                auto previousCmd = cmd;
            }

            
            else if (str[0] != '#') {
                //std::cout << "empty line" << std::endl;
                
            }
                getline (fileIn, str);
            
        }

        endParsing:
        outdata << "P3\n" << w << ' ' << h << "\n255\n";

        scene.renderer();
    }


    
    char *imageNameChar = new char[imageNamePPM.size()+1]; // +1 to account for \0 byte
        std::strncpy(imageNameChar, imageNamePPM.c_str(), imageNamePPM.size());

    CImg<unsigned char> im(imageNameChar); //save at CImg file
    imageNameChar[strlen(imageNameChar)-3] = '\0'; //remove "ppm'
    //std::cout<< "\n" << input_file << "\n";
    char *fileType = "png";
    strncat(imageNameChar, fileType, 4); //add png to file char
    im.save(imageNameChar);
    fileIn.close();
    
    
    triArray.clear();
    triArray.resize(0);

}
    



//evantually, i will have tri mesh defined via
*/
