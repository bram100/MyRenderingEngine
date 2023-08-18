//
//  shape.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 2/7/23.
//

#ifndef shape_hpp
#define shape_hpp

#include <stdio.h>
#include <memory.h>

#include "variables.hpp"

#include "objParameters.hpp"
#include "transform.hpp"

/*
 The Shape class provides access to the raw geometric properties of the primitive, such as its surface area and bounding box, and provides a ray intersection routine
 
 right now, im only going to store location of shape. In intersection test, store color
 */

//extern transformation cameraViewTransformation;
extern matrix4& worldToCamera;
class transformation;
//m is objToWolrd
//mv is worldToObe

//m is cameraToWorld
//mv worldToCamera (all shapes multiplied by this)

class Shapes {
public:
    
    //check if changing this to const imrpoves preformance 
    Shapes();// : objectToWorld(nullptr), worldToObject(nullptr) {}
    Shapes(const transformation* objToWorld, const transformation* worldToObj);

    virtual ~Shapes();
    virtual bool intersect(const ray &ray, float *tHit, localGeo *localGeo) const; ///*const = 0*/;

    virtual bool intersectP(const ray& currentRay) const;

    friend std::ostream& operator<<(std::ostream& os, const Shapes& shape) {
        os << "This is a shape!";
        return os;
    }
    
    
    
    bool intersecttest (color3 color3);

    /*
    void multiplyObjectToWorld( const transformation& newObjectToWorld) {
        
        *const_cast<transformation*>(objectToWorld) = newObjectToWorld * (*objectToWorld);
        
        *const_cast<transformation*>(worldToObject) = inverse(newObjectToWorld) * (*worldToObject);

        }
    */
/*
        void multiplyWorldToObject(const transformation& newWorldToObject) {
            *const_cast<transformation*>(worldToObject) = newWorldToObject * (*worldToObject);
        }
*/

     const transformation* objectToWorld;
     const transformation* worldToObject;

};


/*
struct triangleMesh {
    // triangleMesh Public Methods
    //https://pbr-book.org/3ed-2018/    /Triangle_Meshes
public:
    triangleMesh(const matrix4 &m, int nTrianglesM, const int *vertexPointArray, int nVertices, const point<float> *P);

    // TriangleMesh Data
    const int nTrianglesM, nVertices;
    vector3<int> vertexIndices; //may need to make a special class for this???
    point<float> p;
    //std::unique_ptr<Normal3f[]> triNormal;
    //std::unique_ptr<Vector3f[]> s;
    //std::unique_ptr<Point2f[]> uv;
    //std::shared_ptr<Texture<Float>> alphaMask;
    
    /*
ObjectToWorld: The object-to-world transformation for the mesh.
 triArray: A pointer to an array of vertex indices. For the ith triangle, its three vertex positions are P[triVvertexIndices[3*i]], P[triArray[3*i+1]], and P[triVvertexIndices[3*i+2]].
    

P: An array of nVertices vertex positions.

    
    maxverts 4

    vertex -1 -1 0
    vertex +1 -1 0
    vertex +1 +1 0
    vertex -1 +1 0

    tri 0 1 2
    tri 0 2 3
     */
//};
/*
struct triangle : public shape {
public:
    // Triangle Public Methods
    triangle(const transformation *objToWorld, const transformation *worldToObj, const std::shared_ptr<triangleMesh> &mesh,
             int triNumber) : shape(objToWorld, worldToObj), mesh(mesh) {
        v = &mesh->triArray[3 * triNumber];
        //triMeshBytes += sizeof(*this);
        //faceIndex = mesh->faceIndices.size() ? mesh->faceIndices[triNumber] : 0;
    }

    //Bounds3f ObjectBound() const;
    //Bounds3f WorldBound() const;
    bool Intersect(const ray &ray, float *tHit, intersection *isect,
                   bool testAlphaTexture = true) const;
    //bool IntersectP(const ray &ray, bool testAlphaTexture = true) const;
    //float Area() const;

    //using shape::Sample;  // Bring in the other Sample() overload.
    //Interaction Sample(const Point2f &u, Float *pdf) const;

    // Returns the solid angle subtended by the triangle w.r.t. the given
    // reference point p.
    //float SolidAngle(const Point3f &p, int nSamples = 0) const;

  private:
    // Triangle Private Methods
    /*
    void GetUVs(Point2f uv[3]) const {
        if (mesh->uv) {
            uv[0] = mesh->uv[v[0]];
            uv[1] = mesh->uv[v[1]];
            uv[2] = mesh->uv[v[2]];
        } else {
            uv[0] = Point2f(0, 0);
            uv[1] = Point2f(1, 0);
            uv[2] = Point2f(1, 1);
        }
    }
     */
    // Triangle Private Data
    /*std::shared_ptr<triangleMesh> mesh;
    const int *v;//idk?
    int faceIndex; //idk?
    
};
*/

//idk why two
//a vector of type shaps

void createTransformationMatrix(const vector3<float>& translate, const vector3<float>& rotation, const float axis, const vector3<float>& scale, const int i);

void printShapes();


void makeShapes(const std::string &name, const transformation *ObjectToWorld, const transformation *WorldToObject, objParamMap &paramSet);

extern std::vector<std::shared_ptr<Shapes>> shapesContainer;


//std::shared_ptr<shapeStruct> createSphereShape(const transformation *o2w, const transformation *w2o, const objParamMap &params);


//"The Shape class stores both this transformation and its inverse."

/*
bool WritePlyFile(const std::string &filename, int nTriangles,
                  const int *triArray, int nVertices, const Point3f *P,
                  const Vector3f *S, const Normal3f *N, const Point2f *UV,
                  const int *faceIndices);
*/

/*
class ShapesContainer
{
public:
    void push_back(const std::shared_ptr<Shapes>& shape)
    {
        shapesContainer.push_back(shape);
    }
    
    // Forward the begin() function call to the underlying vector's begin()
     
     // Forward the end() function call to the underlying vector's end()
     auto end()
     {
         return shapesContainer.end();
     }

//protected:
//};
*/

#endif /* shape_hpp */
