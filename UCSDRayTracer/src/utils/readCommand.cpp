//
//  readCommand.cpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 12/14/22.
//





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

transformation translationMatrix;
transformation rotationMatrix;
transformation scaleMatrix;

std::shared_ptr<Material> materialParsed = std::make_shared<Material>();
int countingj = 0;

float w, h;
int maxDepth;
bool animatedBool = false;

bool lightExists;


transformation tranform;
transformation defaultLightTransform; //may add feature later

transformationSet curTransform;
transformationSet curTransformInverse;
static transformCache transformCache;
transformation currentTransform;
transformation currentTransformInverse;

int curTransformIndex;

void output2(std::ofstream& outdata)
{
    outdata << "does this work?" << endl;
}

void readfile(const char* fileName)
{
    
    int newI;
    int myCounting = 0;

    vector3<float> translateVector;
    vector3<float> scaleVector(1.f,1.f,1.f);
    vector3<float> rotationVector;
    float theta;
    
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
                
                
                if (cmd == "fileName" || cmd == "filename") {
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
                    str.erase(0, 5);
                    readValuesFloat(str, 2, valuesf, 3);
                    w = valuesf[0];
                    h = valuesf[1];
                    camera.aspectRatio = w / h;
                    
                    //camera.aspectRatio = aspectRatio;
                    std::cout << "Resolution Set to: X:" << w << " Y:" << h << std::endl;
                }
                
                if (cmd == "resolution") {
                    throw std::invalid_argument("use 'size' not 'resolution");

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
                    
                    
                    vector3<float> positionXYZ (valuesf[0], valuesf[1], valuesf[2]);
                    color3 colorRGB (valuesf[3], valuesf[4], valuesf[4]);
                    
                    params.addOneVector3F("position", positionXYZ);
                    params.addOneColor3("color", colorRGB);

                    lightExists = true;

                    makeLights(cmd, &defaultLightTransform, params);

                }
                
                if (cmd == "point") { //x y z r g b The location of a point source and the color, as in OpenGL.
                    str.erase(0, 5);
                    readValuesFloat(str, 6, valuesf, 3);
                    
                    
                    vector3<float> positionXYZ (valuesf[0], valuesf[1], valuesf[2]);
                    color3 colorRGB (valuesf[3], valuesf[4], valuesf[4]);

                    params.addOneVector3F("position", positionXYZ);
                    params.addOneColor3("color", colorRGB);

                    lightExists = true;
                    
                    makeLights(cmd, &defaultLightTransform, params);

                }
                
                if (cmd == "attenuation") { //const linear quadratic (Sets the constant, linear and quadratic attenuations (default 1,0,0) as in OpenGL. By default there is no attenuation (the constant term is 1, linear and quadratic are 0; that's what we mean by 1,0,0).
                    str.erase(0, 11);
                    readValuesFloat(str, 3, valuesf, 3);
                    
                    
                    makeLights(cmd, &defaultLightTransform, params);

                     

                }
                
                
                if (cmd == "ambient") { //default is .2,.2,.2
                    str.erase(0, 7);
                    //materialParsed = std::shared_ptr<Material>(new Material());

                    readValuesFloat(str, 3, valuesf, 3);
                    color3 ambientColor = convertFloatToColor(valuesf);

                    //color3 ambientColor(valuesf[0], valuesf[1], valuesf[2]);
                    
                    materialParsed->ambient = ambientColor;
                    
                    //new method
                    
                    
                    
                }

                //Note also that if no ambient color or attenuation is specified, you should use the defaults. Note that we allow the ambient value to be changed between objects (so different objects will be rendered with a different ambient term; this is used frequently in the examples).  Finally, note that here and in the materials below, we do not include the alpha term in the color specification.
                
                //materials
                if (cmd == "diffuse") { //r g b
                    str.erase(0, 7);
                    readValuesFloat(str, 3, valuesf, 3);
                    color3 diffuseColor = convertFloatToColor(valuesf);
                    materialParsed->aBRDF.diffuse = diffuseColor;
                    std::cout << materialParsed->aBRDF.diffuse << std::endl;

                }
                
                if (cmd == "specular") { // r g b
                    str.erase(0, 8);
                    readValuesFloat(str, 3, valuesf, 3);
                    color3 specularColor = convertFloatToColor(valuesf);
                    materialParsed->aBRDF.specular = specularColor;

                }
                
                if (cmd == "shininess") { // r g b
                    str.erase(0, 9);
                    readValuesFloat(str, 1, valuesf, 1);
                    materialParsed->aBRDF.shininess = valuesf[0];;

                }
                
                
                if (cmd == "emission") { // r g b
                    str.erase(0, 8);
                    readValuesFloat(str, 3, valuesf, 3);
                    color3 emissionColor = convertFloatToColor(valuesf);
                    materialParsed->aBRDF.emission = emissionColor;

                }

                
                if (cmd == "camera") {
                    str.erase(0, 6);
                    readValuesFloat(str, 10, valuesf, 3);

                    vector3<float> cameraPositionInit(valuesf[0], valuesf[1], valuesf[2]);
                    vector3<float> cameraLookAtInit(valuesf[3], valuesf[4], valuesf[5]);
                    vector3<float> cameraUpInit(valuesf[6], valuesf[7], valuesf[8]);
                    float fovInit = valuesf[9];
                    
                    camera.cameraPosition = cameraPositionInit;
                    camera.cameraLookAt = cameraLookAtInit;
                    camera.cameraUp = cameraUpInit;
                    camera.fov = fovInit;
                    camera.updateCameraParameters();
                    
                    
                    std::cout << "camera position " << camera.cameraPosition << std::endl;
                    
                    std::cout << "Camera set: " << std::endl;
                    
                }
                
                if (cmd == "popTransform") { //retrive
                    str.erase(0, 12);

                    
                    
                    

                    if (curTransformIndex != 0) {
                        curTransformIndex--;
                        
                    }
                    
                  //  translationMatrix.clear();
                    //rotationMatrix.clear();
                    //scaleMatrix.clear();

                    
                    currentTransform = curTransform[curTransformIndex];
                    currentTransformInverse = curTransformInverse[curTransformIndex];
                    

                    }
                       
                if (cmd == "pushTransform") { //add to stack, current working should be idenity matrix
                    str.erase(0, 13);
                    
                    
                    
                    
                    
                   // currentTransformInverse.mt = currentTransform.mt.inverse(currentTransform.mt);


                  //  currentTransform.updateInverseTranpose();
                   // currentTransformInverse.updateInverseTranpose();

                    
                    curTransform[curTransformIndex] = currentTransform;
                    curTransformInverse[curTransformIndex] =currentTransformInverse;

                    curTransformIndex++;

                    }
                      
                if (animatedBool == true) {
                    //these will only impact the creation of the tranformationSet in scene creation

                    if (cmd == "mass") { //mass [bool]
                        str.erase(0, 5);
                        //
                    }

                    
                    if (cmd == "gravity") { //gravity [bool]
                        str.erase(0, 8);
                        //put it at 9.8 meters per second based off time value
                    }
                                  
                    if (cmd == "bounce") { //have to figure out how bounce should be defiend
                        str.erase(0, 7);
                                      
                    }
                                  
                    if (cmd == "node") { //node [parent objectID]
                        //if object hand and parent object arm, then each tranformation for arm needs to adjust hand by the same
                        str.erase(0, 5);
                                    
                    }
                }
                
                //sphere centerx centery centerz radius
                if (cmd == "sphere") {
                    
                    str.erase(0, 7);
                    readValuesFloat(str, 10, valuesf, 3);
                                            
                    objParamMap sphereParams;
                    
                    vector3<float> positionXYZ (valuesf[0], valuesf[1], valuesf[2]);
                    
                    params.addOneVector3F("position", positionXYZ);
                    params.addOneFloat("radius", valuesf[3]);
                    //transformation *o2w = transformCache.lookup(curTransform[0]);
                    //transformation *w2o = transformCache.lookup(inverse(curTransform[0]));
                    
                    
                    //transformation *o2w = &currentTransform;// transformCache.lookup(currentTranform);
                    //transformation inversedTransform = inverse(currentTransform);
                    //transformation *w2o = &inversedTransform;

                    
                    //transformation *w2o = &curTransform[curTransformIndex];
                    //transformation *o2w = (&curTransform[curTransformIndex]);
                   // transformation result = *o2w * cameraViewTransformation;
                   /*
                    createTransformationMatrix(translateVector, rotationVector, theta, scaleVector, curTransformIndex);

                    translateVector.clear();
                    rotationVector.clear();
                    scaleVector.ones();

                    */
                    //string str = "sphere";
                    //makeShapes(str, o2w, w2o, params);
                    
                     /*
                    curTransformInverse[curTransformIndex].mt = curTransform[curTransformIndex].minvt;
                    curTransformInverse[curTransformIndex].minvt = curTransform[curTransformIndex].mt;
*/
                    
                    currentTransformInverse.mt = currentTransform.mt.inverse(currentTransform.mt);

                    
                    
                    currentTransform.updateInverseTranpose();
                    currentTransformInverse.updateInverseTranpose();


                    
                    makeShapes(cmd, &currentTransform, &currentTransformInverse, params);

                    currentTransform.clear();
                    currentTransformInverse.clear();
                    //std::shared_ptr<Material> materialParsed = std::make_shared<Material>(*materialParsed);

                    countingj++;
                    std::cout << "sphere number  " << countingj << std::endl;
                    
                   // curTransformIndex++;
                   
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
                    
                    //transformation *o2w = transformCache.lookup(curTransform[0]);
                    //transformation *w2o = transformCache.lookup(inverse(curTransform[0]));newI

                    /*
                    transformation *o2w = &currentTransform;// transformCache.lookup(currentTranform);
                    transformation inversedTransform = inverse(currentTransform);
                    transformation *w2o = &inversedTransform;
*/
                    

                    triArray.resize(newI+1);

                    triArray[newI] = vector3<int> (valuesi[0], valuesi[1], valuesi[2]);
                    
                    newI++;
                    std::cout << newI << std::endl;
                    
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
                    
                    translateVector.x = valuesf[0];
                    translateVector.y = valuesf[1];
                    translateVector.z = valuesf[2];
                    
                    
                    translationMatrix.translation(translateVector);
                    currentTransform *= translationMatrix;

                    

                }
                
                if (cmd == "rotate") {
                    str.erase(0, 7);
                    readValuesFloat(str, 4, valuesf, 3);
                    
                    rotationVector.x = valuesf[0];
                    rotationVector.y = valuesf[1];
                    rotationVector.z = valuesf[2];

                    theta = valuesf[3];
                    
                    transformation rotationMatrix;
                    
                    
                    rotationMatrix.rotation(theta, rotationVector);
                    currentTransform *= rotationMatrix;


                }
                
                if (cmd == "scale") {
                    str.erase(0, 5);
                    readValuesFloat(str, 4, valuesf, 3);
                                        
                    scaleVector.x = valuesf[0];
                    scaleVector.y = valuesf[1];
                    scaleVector.z = valuesf[2];
                    
                    transformation scaleMatrix;
                    
                    
                    
                    scaleMatrix.scaling(scaleVector);
                    currentTransform *= scaleMatrix;


                }
    
                if (cmd == "end") {
                    goto endParsing;
                }
                auto previousCmd = cmd;
            }

            else if (str[0] != '#') {
                //std::cout << "empty line" << std::endl;
                
                if (triArray.size() > 0) {
                   string str = "triangleMesh";
                   
                    //transformation *o2w = &curTransform[curTransformIndex];// transformCache.lookup(curTransform[0]);
                    //transformation *w2o = (&curTransform[curTransformIndex]);// transformCache.lookup(inverse(curTransform[0]));
                    
                    /*
                    createTransformationMatrix(translateVector, rotationVector, theta, scaleVector, curTransformIndex);
                    
                    translateVector.clear();
                    rotationVector.clear();
                    scaleVector.ones();
                    
                    */
                    
                   params.addOneInt("nTriangles", static_cast<int>(triArray.size()));
                   params.addVector3I("triArray", &triArray[0]);
                   params.addOneInt("nVertices", maxVertArraySize);
                   params.addPoint3F("vertexArray", &vertexPointArray[0]);
                   
                    
                   // curTransformInverse[curTransformIndex].mt = transformation::Transpose(inverse(curTransform[curTransformIndex].mt));
                   // curTransformInverse[curTransformIndex].minvt = curTransform[curTransformIndex].mt;
                //    curTransformInverse[curTransformIndex].updateInverseTranpose;

                    
                    currentTransformInverse.mt = currentTransform.mt.inverse(currentTransform.mt);

                    
                    
                    currentTransform.updateInverseTranpose();
                    currentTransformInverse.updateInverseTranpose();


                    makeShapes(str, &currentTransform, &currentTransformInverse, params);
                    
                    currentTransform.clear();
                    currentTransformInverse.clear();

                   // std::shared_ptr<Material> materialParsed = std::make_shared<Material>(*materialParsed);

                   // curTransformIndex++;
                    
                    triArray.clear();
                    triArray.resize(0);
                    newI = 0;
               }
            }
                getline (fileIn, str);
            
        }
        endParsing:
        
        //handle older scenes
        
        if (lightExists == false) {
            vector3<float> positionXYZ (1.f, 1.f, 1.f);
            color3 colorRGB (1.f, 1.f, 1.f);
            
            params.addOneVector3F("position", positionXYZ);
            params.addOneColor3("color", colorRGB);

            lightExists = true;

            makeLights("point", &defaultLightTransform, params);

        }
        
        outdata << "P3\n" << w << ' ' << h << "\n255\n";
        scene.renderer();
    }

    triArray.clear();
    triArray.resize(0);
    fileIn.close();


}

void closefile(const char* fileName) {
    
    char *imageNameChar = new char[imageNamePPM.size()+1]; // +1 to account for \0 byte
        std::strncpy(imageNameChar, imageNamePPM.c_str(), imageNamePPM.size());

    CImg<unsigned char> im(imageNameChar); //save at CImg file
    imageNameChar[strlen(imageNameChar)-3] = '\0'; //remove "ppm'
    //std::cout<< "\n" << input_file << "\n";
    char *fileType = "png";
    strncat(imageNameChar, fileType, 4); //add png to file char
    im.save(imageNameChar);
    
    
}
