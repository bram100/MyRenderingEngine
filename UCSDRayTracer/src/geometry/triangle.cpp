//
//  triangle.cpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 5/7/23.
//

#include "triangle.hpp"

#include "camera.hpp"
//#include "ray.hpp"

//so i have

extern Camera camera;


// Implement the constructor
bool triangleMesh::intersect(const ray &ray, float *tHit, localGeo *localGeoPos) const
{
    
    //this isnt needed?
    //we just call triangle intersect, not mesh intersect?
    
    
    return true;
}



std::vector<std::shared_ptr<Shapes>> createTriangleMesh(
    const transformation *objectToWorld, const transformation *worldToObject, int nTriangles, const vector3<int> *triArray,
    int nVertices, const point3<float> *vertexPointArray, /*const vector3<float> *s, const normal<float> *n,  const std::shared_ptr<Texture<Float>> &alphaMask , const std::shared_ptr<Texture<Float>> &shadowAlphaMask ,*/ const int *faceIndices)

//will iterate over the connectivity information, select the corresponding vertex attributes, and create the individual triangles using these attributes
{
    
    
    
    std::shared_ptr<triangleMesh> mesh = std::make_shared<triangleMesh>(
        *objectToWorld, *worldToObject, nTriangles, triArray, nVertices, vertexPointArray/*, s, n , alphaMask, shadowAlphaMask*/, faceIndices);
    

    /*
    std::cout << "vertexPointArray[3 * triNumber]: "
              << mesh->vertexPointArray[0].x << ", "
              << mesh->vertexPointArray[1].y << ", "
              << mesh->vertexPointArray[2].z << std::endl;
*/
    
   // std::cout << "numTri: " << mesh->nTriangles << std::endl;

    
    std::vector<std::shared_ptr<Shapes>> triangleShapes;

    // Create triangle objects and add them to the vector
    for (int i = 0; i < nTriangles; ++i) {
        // Calculate the vertex indices for the current triangle
        //provides the first variable of tir x y z
        const int* indices = &triArray[i].x;

        // Create a triangle object and assign it to shared pointer
        std::shared_ptr<Triangle> triangle(new Triangle(
            objectToWorld, worldToObject, mesh, i));
        
        //std::cout << triangle << std::endl;
        
        // Add the triangle object to the vector
        
        triangleShapes.push_back(triangle);
        
    }
    
    /*
    
    // this function needs to define normals and texture coords, and maybe Connectivity Information, vertex positions. PBRT has this information stored in the mesh but assinged to each triangle. Each triagnle is store din the mesh.
    std::shared_ptr<triangleMesh> mesh = std::make_shared<triangleMesh>(
        *objectToWorld, *worldToObject, nTriangles, triArray, nVertices, vertexPointArray /*, s, n , alphaMask, shadowAlphaMask*//*, faceIndices);
    
    
    std::vector<std::shared_ptr<Shapes>> tri;
    tri.reserve(nTriangles);
    
    //2. Triangle Creation: Using the connectivity information, the function iterates over the indices to create individual triangles. For each set of three indices, it selects the corresponding vertex positions, normals, and texture coordinates from the respective arrays.
    
    std::vector<std::shared_ptr<Shapes>> triangleShapes;
    triangleShapes.reserve(nTriangles);

    // Triangle Creation: Iterate over the indices to create individual triangles.
    
    
    
    
    
    for (int i = 0; i < nTriangles; ++i) {
        
        //const point3<int>* vertexPointArray = mesh->vertexPointArray.get();
        
        // Access the first element
        point3<int> firstElement = vertexPointArray[0];
        
        // Access the second element
        //point3<int> secondElement = vertexPointArray[4];
        point3<int> secondElement = *(vertexPointArray + 1);

        
        // Get the indices of the vertices for the current triangle
        int vertexIndex1 = mesh->triArray[i].x;
        int vertexIndex2 = mesh->triArray[i].y;
        int vertexIndex3 = mesh->triArray[i].z;
        //vector3<int> &meow = mesh->triArray.get() + i;

        // Retrieve the actual vertex positions using the indices
        point3<int> vertex1 = mesh->vertexPointArray[vertexIndex1];
        point3<int> vertex2 = mesh->vertexPointArray[vertexIndex2];
        point3<int> vertex3 = mesh->vertexPointArray[vertexIndex3];

        // Create a triangle using the retrieved vertices
        triangle currentTriangle(objectToWorld, worldToObject, mesh, i);

        // Do something with the created triangle, such as adding it to a container or performing operations on it
    }

    
    for (int i = 0; i < nTriangles; i++) {
        // Select the corresponding vertex indices.
        
       // int v0 = vertexPointArray[0].x;

        const int *v = reinterpret_cast<const int*>(&mesh->vertexPointArray[0]);
        std::cout << "v: " << *v << std::endl;
        const point3<int>& l = mesh->vertexPointArray[3 * i];
        int v0 = l.x;
        int v1 = l.y;
        int v2 = l.z;

        
        vector3<int> a;
        a[0] = 1;
        a[1] = 1;
        a[2] = 1;

        int k = 5;
        const int *j = &k;
        
        
        
        
        
        // Create a new triangle shape and add it to the vector.
        std::shared_ptr<Shapes> triangleShape = std::make_shared<triangle>(objectToWorld, worldToObject, mesh, i);
        triangleShapes.push_back(triangleShape);
    }
    
    


/*
    for (int i = 0; i < nTriangles; ++i) {
       // const int *v = reinterpret_cast<const int*>(&mesh->vertexPointArray[3 * i]);
        //tri.push_back(std::make_shared<triangle>(objectToWorld, worldToObject, mesh, i));
        
        //v = &mesh->vertexIndices[3 * triNumber];

        const int *vValue = reinterpret_cast<const int*>(&mesh->vertexPointArray[3 * i]);
        tri.push_back(std::make_shared<triangle>(objectToWorld, worldToObject, mesh, i));
        
 */
        //std::shared_ptr<TriangleMesh> sharedMesh = std::make_shared<TriangleMesh>(mesh);

        // Create a Triangle object.
        //triangle triangle(&objectToWorld, &worldToObject, false, mesh, i);
        //In this example, you need to provide the necessary inputs for the Triangle constructor:

    
    
    //3. Triangle Data: The function constructs data structures to store the individual triangles. Each triangle is defined by three vertices with their associated attributes, such as position, normal, and texture coordinates. These triangles form the mesh geometry.
        
    
    
    
    //4. Additional Data: Depending on the rendering system, the function might also compute additional data for the triangles, such as bounding boxes or surface area information. These additional data can help optimize the rendering process by enabling spatial acceleration structures like bounding volume hierarchies (BVH) or spatial partitioning.

    


        
    
    return triangleShapes;// being a vector of shapes
    
    
}




//separately store entire triangle meshes with an array of vertex positions where each individual triangle just stores three offsets into this array for its three vertices
std::vector<std::shared_ptr<Shapes>> createTriangleMeshShape(const transformation *o2w, const transformation *w2o, const objParamMap &params, int triMeshIndex) {
    
    //main function of this function is just to define variables to pass into createTriangleMesh
    
    //1. passing in vertex positions, vertex normals, texture coordinates (if applicable), and the indices that specify the connectivity of the vertices to form triangles

    int nTriInt, vertInt, vertPInt, SInt, NInt, UVInt, curMaterial;
    
    float vertFloat, vertPFloat;
    
    const int nTriangles = params.findOneInt("nTriangles", nTriInt); //shouldt this be a constant value not a pointer to the first obj of an array?
    
    //this needs to change somehow, it should be a const int pointer
    const vector3<int> *triArray = params.findVector3I("triArray", &vertInt) ;
    
    const int nVertices = params.findOneInt("nVertices", int(1));
    //const point3<float>* P = params.findPoint3F("P", &PInt);
    //const vector3<float>* S = params.findVector3F("S", &SInt);
    //const normal<float>* N = params.findNormalF("N", &NInt);
    //const point3<float>* uv = params.findPoint3F("UV", &UVInt);
    int faceIndices = params.findOneInt("faceIndices", int(1));
    //const Material *material = params.findMaterial("material", &curMaterial);

    const point3<float> *vertexPointArray = params.findPoint3F("vertexArray", &vertPInt);
    

    
    
    
    /*
    for (int i = 0; i < nTriangles; ++i)
            tris.push_back(std::make_shared<Triangle>(ObjectToWorld, WorldToObject,
                                                      reverseOrientation, mesh, i));
    */
    
    
    //static std::vector<vector3<int>> vertexPointArray;
    //Float zmin = params.FindOneFloat("zmin", -radius);
    //Float zmax = params.FindOneFloat("zmax", radius);
    //Float phimax = params.FindOneFloat("phimax", 360.f);
    //return makeTriangleMesh2(o2w, w2o, nTriangles, &vertexPointArray, nVertices,  &P, &S, &N, &uv, /* &alphaMask, &shadowAlphaMask, */ &faceIndices);
    
    
    
    
    
    //2. Triangle Creation: Using the connectivity information, the function iterates over the indices to create individual triangles. For each set of three indices, it selects the corresponding vertex positions, normals, and texture coordinates from the respective arrays.
    
    

    
    
    //3. Triangle Data: The function constructs data structures to store the individual triangles. Each triangle is defined by three vertices with their associated attributes, such as position, normal, and texture coordinates. These triangles form the mesh geometry.
        
    
    
    
    //4. Additional Data: Depending on the rendering system, the function might also compute additional data for the triangles, such as bounding boxes or surface area information. These additional data can help optimize the rendering process by enabling spatial acceleration structures like bounding volume hierarchies (BVH) or spatial partitioning.
    
    //createTriangleMesh(
    
    
    
    //5. Mesh or Shape Object: The function returns a mesh or shape object that holds the created triangles and any additional data. .
    
    //make traingle mesh, so i have to be returning the pointer to the first location of each object

    
    
    return createTriangleMesh(o2w, w2o, nTriangles, triArray, nVertices, vertexPointArray, /* S, N, */ &faceIndices);


}


template <typename T>
point3<T> operator*(const point3<T>& vec, const matrix4& matrix) {
    point3<T> transformedVec;

    // Assuming that the 'm' member in matrix4 is accessible here
    transformedVec[0] = vec[0] * matrix.m[0][0] + vec[1] * matrix.m[1][0] + vec[2] * matrix.m[2][0] + matrix.m[3][0];
    transformedVec[1] = vec[0] * matrix.m[0][1] + vec[1] * matrix.m[1][1] + vec[2] * matrix.m[2][1] + matrix.m[3][1];
    transformedVec[2] = vec[0] * matrix.m[0][2] + vec[1] * matrix.m[1][2] + vec[2] * matrix.m[2][2] + matrix.m[3][2];
    // The 4th value of point3 is 1.0f, as you mentioned in the comments in your code
    transformedVec[3] = vec[0] * matrix.m[0][3] + vec[1] * matrix.m[1][3] + vec[2] * matrix.m[2][3] + matrix.m[3][3];

    return transformedVec;
}




int current = 0;
bool Triangle::intersect(const ray &currentRay, float *tHit, localGeo *localGeoPos) const
{
    
    ray transformedRay = worldToObject->operator*(currentRay);

    /*
    matrix4 testing = worldToObject->mt;
    ray transformedRay = currentRay * testing;
     */
     
    
    const point3<float>* v = mesh->vertexPointArray.get();
    const vector3<int>* thisArray = mesh->triArray.get();
   
    point3<float> v0 = point3<float>(v[thisArray[faceIndex][0]]);
    point3<float> v1 = point3<float>(v[thisArray[faceIndex][1]]);
    point3<float> v2 = point3<float>(v[thisArray[faceIndex][2]]);

/*
    point3<float> v00 = multPointMatrix<float>(camera.worldToCamera, v0);
    point3<float> v11 = multPointMatrix<float>(camera.worldToCamera, v1);
    point3<float> v22 = multPointMatrix<float>(camera.worldToCamera, v2);

    v0 = v00;
    v1 = v11;
    v2 = v22;
    */
    //compute planes normal
    vector3<float> normalEdge1 = v1 - v0; //normalizing makes no diff?
    vector3<float> normalEdge2 = v2 - v0;//normalizing makes no diff?

    //normal - find the perpendicular/face
    vector3<float> N = normalEdge1^normalEdge2; // N = cross product

    //magnitude of the resulting vector crossProduct is equal to the area of the parallelogram formed by edge1 and edge2
    float area2 = N.Length();
    
    //this will apply transofmrations from the shape class?
    //ray transformedRay = ray * objectToWorld;
    
    // STEP 1: finding P
    
    // check if the ray and plane are parallel.
    float NdotRayDirection = N*transformedRay.lookAt; //dot product

    auto k = fabs(NdotRayDirection); //float absolutre
    if (k < kEpsilon) // fabs is "float absolute values" if its almost 0 fabs() returns absolute value
        
        return false; // they are parallel, so they don't intersect!

    // compute d (signed distance from the origim) parameter
    float d = -(N*v0); //vector<float> * point3<float> //why negative
    
    // compute t (equation 3)
    float t = -(N*transformedRay.lookFrom + d) / NdotRayDirection; //dot
    
    // check if the triangle is behind the ray
    if (t < 0)
        
        return false; // the triangle is behind
 
    // compute the intersection point using equation 1
    vector3<float> P = transformedRay.lookFrom + (transformedRay.lookAt * t); //not sure if * is right form of multiplcaiton
 
    // Step 2: inside-outside test
    vector3<float> cross; // vector perpendicular to triangle's plane
 
    // edge 0
    vector3<float> edge0 = v1 - v0; //actually isnt this a re/definintion?
    vector3<float> vp0 = P - v0; //
    cross = edge0^vp0; //cross product
    if ((N*cross) < 0) //clockwise vs counterclockwise reverse >
        
        return false; // P is on the right side
 
    // edge 1
    vector3<float> edge1 = v2 - v1; //actually isnt this a re/definintion?
    vector3<float> vp1 = P - v1;
    cross = edge1^vp1; //cross product of edge1 and
    if ((N*cross) < 0) //clockwise vs counterclockwise reverse >
        
        return false; // P is on the right side
 
    // edge 2
    vector3<float> edge2 = v0 - v2; //actually isnt this a re/definintion?
    vector3<float> vp2 = P - v2;
    cross = edge2^vp2;
    if ((N*cross) < 0) //clockwise vs counterclockwise reverse >
        
        return false; // P is on the right side;

    localGeoPos->pos = transformedRay.pointAt(t);  // Calculate the intersection position
    normal<float> normal(N.x, N.y, N.z);
    
    localGeoPos->normal = normal; //not sure if this is right ????
    
    *tHit = t;  // Update the intersection distance
    
    return true; // this ray hits the triangle
}

