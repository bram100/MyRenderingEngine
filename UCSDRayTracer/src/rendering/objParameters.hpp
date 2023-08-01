//
//  objParameters.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/30/23.
//

#ifndef objParameters_hpp
#define objParameters_hpp

#include <stdio.h>
#include <memory>
#include <string>


#include <map>
#include <string>
#include <variant>
#include "vector.hpp"
#include <vector>
#include "point.hpp"

#include "normal.hpp"
#include "color.hpp"
#include "material.hpp"

template <typename T>
struct objParametersItem {
    // ParamSetItem Public Methods
    objParametersItem(const std::string &key, std::unique_ptr<T[]> val,
                 int nValues = 1);

    // ParamSetItem Data
    const std::string key;
    const std::unique_ptr<T[]> values;
    const int nValues;
    mutable bool lookedUp = false;
};

template <typename T>
objParametersItem<T>::objParametersItem(const std::string &key, std::unique_ptr<T[]> v, int nValues)
    : key(key), values(std::move(v)), nValues(nValues) {}


class objParamMap {
public:
    
    objParamMap() {};
    
    void addOneInt(const std::string &key, int value);
    void addOneFloat(const std::string &key, const float value);
    void addOneVector3F(const std::string &key, const vector3<float> value);
    void addOnePoint3F(const std::string &key, const point3<float> value);

    void addOneColor3(const std::string &key, const color3 value);
    void addMaterial(const std::string &key, const Material* value);

    
    void addVector3I(const std::string &key, const vector3<int>* value);
    void addVector3F(const std::string &key, const vector3<float>* value);
    void addInt(const std::string &key, int* value);
    void addFloat(const std::string &key, const float* value);
    
    void addPoint3F(const std::string &key, const point3<float>* value);
    void addPoint3I(const std::string &key, const point3<int>* value);

    void addNormalF(const std::string &key, const normal<float> value);
    //void printValues() const;
    
    
    
    
    //find single objects
    const float findOneFloat(const std::string &, float d) const ;
    const int findOneInt(const std::string &, int d) const;
    
    point3<float> findOnePoint3F(const std::string &, point3<float> d) const ;
    vector3<float> findOneVector3F(const std::string &, const vector3<float> d) const;

    color3 findOneColor3(const std::string &, color3 d) const ;


    //vector3<int> findOneVector3I(const std::string &, const vector3<int> d) const;

   // normal<float> findOneNormalF(const std::string &, const normal<int> d) const;

//findOneInt will take an object and return a pointer
//findInt will take a pointer and return a pointer

    
    //find an array of objects, but return the pointer to the memory lcoation fo the first object
    const point3<float> *findPoint3F(const std::string &, int *nValues) const;
    
    const point3<int> *findPoint3I(const std::string &, int *nValues) const;
    const Material *findMaterial(const std::string &, int *nValues) const;

    //const point3<int>* findPoint3I(const std::string& key) const;
    
    const normal<float> *findNormalF(const std::string &,  int *nValues) const;
    const vector3<float> *findVector3F(const std::string &, int *nValues) const;
    const vector3<int> *findVector3I(const std::string &,  int *nValues) const;
    const int *findInt(const std::string &, int *nValues) const;


private:
    //ok so const color3 didnt work but const color3* fixed my bug
    std::map<std::string, std::variant<float, const Material*, color3, const color3* , int*, float*, const void*, const int*,
        const point3<float>, point3<float>,  const point3<float>*, const point3<int>*,
        const vector3<float>*, const vector3<int>*, int, vector3<float> >> myMap;
};







#endif /* objParameters_hpp */
