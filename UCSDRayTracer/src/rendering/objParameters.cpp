//
//  objParameters.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 3/30/23.
//

#include "objParameters.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include "vector.hpp"
#include <iostream>
#include "point.hpp"
#include <variant>
#include "color.hpp"
#include <tuple> //for std::get
//#include "material.hpp"

/*
 constexpr bool holds_alternative( const std::variant<Types...>& v ) noexcept;
 (since C++17)
 Checks if the variant v holds the alternative T. The call is ill-formed if T does not appear exactly once in Types...
 Parameters

 */

#define ADD_PARAM_TYPE(T, vec) \
    (vec).emplace_back(new ParamSetItem<T>(key, std::move(values), nValues));
#define LOOKUP_PTR(vec)             \
    for (const auto &v : vec)       \
        if (v->key == key) {      \
            *nValues = v->nValues;  \
            v->lookedUp = true;     \
            return v->values.get(); \
        }                           \
    return nullptr
#define LOOKUP_ONE(vec)                           \
    for (const auto &v : vec)                     \
        if (v->key == key && v->nValues == 1) { \
            v->lookedUp = true;                   \
            return v->values[0];                  \
        }                                         \
    return d

/*
void objParamMap::addMaterial(const std::string &key, const Material* value) {
    myMap[key] = value;
}*/

void objParamMap::addVector3I(const std::string &key, const vector3<int>* value) {
    myMap[key] = value;
}


void objParamMap::addPoint3I(const std::string& key, const point3<int>* value) {
    myMap[key] = value;
}

void objParamMap::addVector3F(const std::string &key, const vector3<float>* value) {
    myMap[key] = value;
}

void objParamMap::addPoint3F(const std::string &key, const point3<float>* value) {
    myMap[key] = value;
}

/*
void objParamMap::addPoint3I(const std::string& key, const point3<int>* value) {
    myMap[key] = value;


    //myMap[key] = value;
    
    std::cout << "memory " << value <<std::endl;
    
    
}
*/


void objParamMap::addOneInt(const std::string& key, int value) {
    myMap[key] = value;
}

void objParamMap::addOneFloat(const std::string& key, float value) {
    std::cout << "Value: " << std::endl;
    myMap[key] = value;
    
}

void objParamMap::addOneVector3F(const std::string& key, vector3<float> value) {
    std::cout << "Value: " << std::endl;
    myMap[key] = value;
}

void objParamMap::addOneColor3(const std::string& key, color3 value) {
    std::cout << "Value: " << std::endl;
    //myMap[key] = std::get<color3>(value);
    myMap[key] = value;

}

/*
void objParamMap::addOnePoint3F(const std::string& key, point3<float> value) {
    std::cout << "Value: " << std::endl;
    myMap[key] = value;
    //myMap[key] = point3(value);

}
*/



void objParamMap::addFloat(const std::string &key, const float* value) {
    //float existingValue = myMap.at(key);
    myMap[key] = value;
}
/*
void objParamMap::printValues() const {
    for (const auto &[key, value] : myMap) {
        std::cout << "Value of key '" << key << "': ";
        if (auto intValue = std::get_if<int>(&value)) {
            std::cout << *intValue;
        } else if (auto vectorValue = std::get_if<std::vector<int>>(&value)) {
            for (int x : *vectorValue) std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}
*/


//find one
/*
float objParamMap::findOneFloat(const std::string &name, float d) const {

    auto it = myMap.find(name);
    if (it != myMap.end() && std::holds_alternative<float>(it->second)) {
        return std::get<float>(it->second);
    }
    return d;

}
*/
const int objParamMap::findOneInt(const std::string &name, int d) const {
    auto it = myMap.find(name);
    if (it != myMap.end() && std::holds_alternative<int>(it->second)) {
        return std::get<int>(it->second);
    }
    return d;
}

const float objParamMap::findOneFloat(const std::string &name, float d) const {

    auto it = myMap.find(name);
    if (it != myMap.end() && std::holds_alternative<float>(it->second)) {
        return std::get<float>(it->second);
    }
    std::cout << "D: " << d << std::endl;
    return d;

}

vector3<float> objParamMap::findOneVector3F(const std::string &name, vector3<float> d) const {
    auto it = myMap.find(name);
    if (it != myMap.end() && std::holds_alternative<vector3<float>>(it->second)) {
        return std::get<vector3<float>>(it->second);
    }
    return d;
}
    

point3<float> objParamMap::findOnePoint3F(const std::string &name, point3<float> d) const {
        auto it = myMap.find(name);
        if (it != myMap.end() && std::holds_alternative<point3<float>>(it->second)) {
            return std::get<point3<float>>(it->second);
        }
        return d;

    }




/*
vector3<int> objParamMap::findOneVector3I(const std::string &key, vector3<int> d) const {
    //may be wrong????
    
    auto it = myMap.find(key);
    if (it != myMap.end() && std::holds_alternative<vector3<int>>(it->second)) {
        return std::get<vector3<int>>(it->second);
    } else {
        return d;
    }
}
 

vector3<float> objParamMap::findOneVector3F(const std::string &key, vector3<float> d) const {
    //may be wrong????
    
    auto it = myMap.find(key);
    if (it != myMap.end() && std::holds_alternative<vector3<float>>(it->second)) {
        return std::get<vector3<float>>(it->second);
    } else {
        return d;
    }
}
 */
/*
point3<float> objParamMap::findOnePoint3F(const std::string &key, point3<float> d) const {
    //may be wrong????
    
    
    auto it = myMap.find(key);
    if (it != myMap.end() && std::holds_alternative<point3f>(it->second)) {
        return std::get<point3f>(it->second);
    }
    return d;
}
*/

//find many , through pointer to the first


const point3<float>* objParamMap::findPoint3F(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const point3<float>*>(value)) {
            *nValues = 1;
            return std::get<const point3<float>*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}
/*
const Material* objParamMap::findMaterial(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const Material*>(value)) {
            *nValues = 1;
            return std::get<const Material*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}
*/



const point3<int>* objParamMap::findPoint3I(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const point3<int>*>(value)) {
            *nValues = 1;
            return std::get<const point3<int>*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}


const vector3<int>* objParamMap::findVector3I(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const vector3<int>*>(value)) {
            *nValues = 1;
            return std::get<const vector3<int>*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}








const vector3<float>* objParamMap::findVector3F(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const vector3<float>*>(value)) {
            *nValues = 1;
            return std::get<const vector3<float>*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}









const int* objParamMap::findInt(const std::string& key, int* nValues) const {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        const auto& value = it->second;
        if (std::holds_alternative<const int*>(value)) {
            return std::get<const int*>(value);
        }
    }
    throw std::runtime_error("Invalid value type or key not found in objParamMap");
}









/*
bool readValuesInt2(std::string& command, const int numvals, int values[10], int lenght) {
    int f;
    std::stringstream stringStream (command);
    for (int i = 0; i < numvals; i++) {
        stringStream >> f;
        values[i] = f;
    }
}

bool readValuesFloat2(objParameters params, const int numvals, float valuesf[10], int lenght) {
    
    float f;
    std::stringstream stringStream (params);
    //std::setprecision(5);
    
    for (int i = 0; i < numvals; i++) {
        stringStream >> f;
        valuesf[i] = f;
    }
}
*/

/*
float *objParameters::findOneFloat(const std::string &name, float d) const {
    for (const auto &f : floats)
        if (f->name == name && f->nValues == 1) {
            f->lookedUp = true;
            return f->values[0];
        }
    return d;
}

const float *objParameters::findFloat(const std::string &name, int *n) const {
    for (const auto &f : floats)
        if (f->name == name) {
            *n = f->nValues;
            f->lookedUp = true;
            return f->values.get();
        }
    return nullptr;
}

const int *objParameters::findInt(const std::string &name, int *nValues) const {
    LOOKUP_PTR(ints);
}

const bool *objParameters::findBool(const std::string &name, int *nValues) const {
    LOOKUP_PTR(bools);
}

int objParameters::findOneInt(const std::string &name, int d) const {
    LOOKUP_ONE(ints);
}

bool objParameters::findOneBool(const std::string &name, bool d) const {
    LOOKUP_ONE(bools);
}

//i need to leanr more about macros,if this works. What is this code doing?
#define ADD_PARAM_TYPE(T, vec) \
    (vec).emplace_back(new ParamSetItem<T>(name, std::move(values), nValues));
#define LOOKUP_PTR(vec)             \
    for (const auto &v : vec)       \
        if (v->name == name) {      \
            *nValues = v->nValues;  \
            v->lookedUp = true;     \
            return v->values.get(); \
        }                           \
    return nullptr
#define LOOKUP_ONE(vec)                           \
    for (const auto &v : vec)                     \
        if (v->name == name && v->nValues == 1) { \
            v->lookedUp = true;                   \
            return v->values[0];                  \
        }                                         \
    return d


*/
