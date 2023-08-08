//
//  triangle.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 5/7/23.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include "shape.hpp"



struct triangleMesh {
public:
    triangleMesh(const transformation& ObjToWorld = transformation(),
                 const transformation& WorldToObj = transformation(),
                 int nTriangles = 0,
                 const vector3<int>* triArray = nullptr,
                 int nVertices = 0,
                 const point3<float>* vertexPointArray = nullptr,
                 const int* faceIndices = nullptr)
        : nTriangles(nTriangles),
          nVertices(nVertices),
          triArray(std::make_unique<vector3<int>[]>(nTriangles)),
          vertexPointArray(std::make_unique<point3<float>[]>(nVertices)),
          //material(std::make_unique<Material>(aBRDF)),

    faceIndices(std::make_unique<int[]>(nTriangles)) {
        
        
        //why is this needed here but not other places
        for (int i = 0; i < nVertices; ++i) {
            this->vertexPointArray[i] = vertexPointArray[i];
        }
        
        for (int i = 0; i < nTriangles; ++i) {
            this->triArray[i] = triArray[i];
        }

        

    }
    
    bool intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const;

    bool intersectP(const ray &ray) const;



    // Rest of the member variables
    int nTriangles, nVertices, triArraySize;
    BRDF aBRDF;
    std::unique_ptr<vector3<int>[]> triArray;
    std::unique_ptr<point3<float>[]> vertexPointArray;
    std::unique_ptr<normal<float>[]> n;
    std::unique_ptr<vector3<float>[]> s;
    std::unique_ptr<point3<float>> uv;
    std::unique_ptr<int[]> faceIndices;
    std::unique_ptr<Material> material;
    transformation objToWorld;
    transformation worldToObj;
};


/*
 ObjectToWorld: The object-to-world transformation for the mesh.
 nTriangles: The total number of triangles in the mesh.
 triArray: A pointer to an array of vertex indices. For the ith triangle, its three vertex positions are P[triArray[3*i]], P[triArray[3*i+1]], and P[triArray[3*i+2]].
 nVertices: The total number of vertices in the mesh.
 P: An array of nVertices vertex positions.
 S: An optional array of tangent vectors, one per vertex in the mesh. These are used to compute shading tangents.
 N: An optional array of normal vectors, one per vertex in the mesh. If present, these are interpolated across triangle faces to compute shading normals.
 UV: An optional array of parametric  values, one for each vertex.
 alphaMask: An optional alpha mask texture, which can be used to cut away parts of triangle surfaces.

 */


std::vector<std::shared_ptr<Shapes>> createTriangleMesh(
    const transformation *o2w, const transformation *w2o, int nTrianlges, const vector3<int> *triArray, int nVertices, const point3<float> *vertexPointArray, /*, const vector3<float> *s, const normal<float> *n, */const int *faceIndeces);



std::vector<std::shared_ptr<Shapes>> createTriangleMeshShape(
    const transformation *o2w, const transformation *w2o, const objParamMap &params, int triMeshIndex);

//Triangle doesn’t store much data—just a pointer to the parent

class Triangle : public Shapes {
  public:
    // Sphere Public Methods
    Triangle( const transformation *o2w, const transformation *w2o, const std::shared_ptr<triangleMesh> &mesh, const int &triNumber) : Shapes(o2w, w2o), mesh(mesh) {
        
        v = reinterpret_cast<const float*>(&mesh->vertexPointArray[3 * triNumber]);

        faceIndex = triNumber; /* mesh->faceIndices.size() ? */ //mesh->faceIndices[triNumber]; /*: 0;*/
    }
    

    //bool intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const;
    bool intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const override;
    
    bool intersectP(const ray &ray) const override;


  private:
    std::shared_ptr<triangleMesh> mesh;
    const float *v; //store the address of the vertex indices for a specific triangle within a TriangleMesh objec - points to the starting address of the array of vertex indices for the triangle.
    int faceIndex;
    
    
};

std::shared_ptr<Shapes> createSphereShape(const transformation *o2w, const transformation *w2o, const objParamMap &params);






#endif /* triangle_hpp */



