//
//  transform.hpp
//  UCSD_CSE168_HW1
//
//  Created by Brendan Mulcahey on 1/10/23.
//

#ifndef transform_hpp
#define transform_hpp

#include <stdio.h>
#include "matrix.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "point.hpp"
#include <vector>
#include "ray.hpp"
/*
 Store the local geometry at the intersection point. May need to store
other quantities (eg. texture coordinate) in a more complicated
raytracer.
*/

const int maxTransforms = 100;

class transformation {
public:
        
    transformation() {}
    transformation(const float mat[4][4]) {
        mt = matrix4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0],
                    mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1],
                      mat[2][2], mat[2][3], mat[3][0], mat[3][1], mat[3][2],
                      mat[3][3]);
        minvt = transformation::Transpose(inverse(mt));
        
    }
    
    transformation(const matrix4 &mt) : mt(mt), minvt(transformation::Transpose(inverse(mt))) {}
    transformation(const matrix4 &mt, const matrix4 &minvt) : mt(mt), minvt(minvt) {}
    
    // Constructor using a look-at configuration
    //i have no idea what this is for????
    transformation(const vector3<float>& from, const vector3<float>& to, const vector3<float>& up) {
            vector3<float> forward = from - to;
            normalize(forward);
            vector3<float> right = (up ^ forward); // Cross product
            normalize(right);
            vector3<float> newup = (forward ^ right); // Cross product

            // Create the transformation matrix using initializer list
            mt = matrix4{
                {right.x, right.y, right.z, 0.0f},
                {newup.x, newup.y, newup.z, 0.0f},
                {forward.x, forward.y, forward.z, 0.0f},
                {from.x, from.y, from.z, 1.0f}
            };

            minvt = transformation::Transpose(inverse(mt));
            
            
        }
    
    
    
    matrix4 inverse(const matrix4& m) const {
        matrix4 inv;  // Placeholder for the inverse matrix
        matrix4 aug = m;  // Augmented matrix (original matrix + identity matrix)

        // Perform Gaussian elimination with partial pivoting
        int n = 4;  // Size of the matrix (assuming it's a 4x4 matrix)
        for (int i = 0; i < n; i++) {
            // Partial pivoting - find the row with the largest pivot element
            int pivotRow = i;
            float pivotValue = std::abs(aug[i][i]);
            for (int k = i + 1; k < n; k++) {
                if (std::abs(aug[k][i]) > pivotValue) {
                    pivotRow = k;
                    pivotValue = std::abs(aug[k][i]);
                }
            }

            // Swap rows to bring the pivot element to the diagonal
            if (pivotRow != i) {
                std::swap_ranges(aug[i], aug[i] + n, aug[pivotRow]);
                std::swap_ranges(inv[i], inv[i] + n, inv[pivotRow]);
            }

            // Scale the pivot row to make the pivot element equal to 1
            float pivotScale = 1.0f / aug[i][i];
            for (int j = 0; j < n; j++) {
                aug[i][j] *= pivotScale;
                inv[i][j] *= pivotScale;
            }

            // Eliminate the other rows
            for (int k = 0; k < n; k++) {
                if (k != i) {
                    float factor = aug[k][i];
                    for (int j = 0; j < n; j++) {
                        aug[k][j] -= factor * aug[i][j];
                        inv[k][j] -= factor * inv[i][j];
                    }
                }
            }
        }

        return inv;
    }
    

    /*
    friend transformation inverse(const transformation &t) {
            return transformation(t.minvt, t.mt);
        }*/
    
    //https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/matrix-inverse/matrix-inverse.html
    //friend matrix4 inverse(const matrix4 &) {

    
   
    vector4<float> operator*(const vector4<float>* vec) const {
        vector4<float> result;

        // Perform matrix-vector multiplication
        result.x = mt[0][0] * vec->x + mt[0][1] * vec->y + mt[0][2] * vec->z + mt[0][3] * vec->w;
        result.y = mt[1][0] * vec->x + mt[1][1] * vec->y + mt[1][2] * vec->z + mt[1][3] * vec->w;
        result.z = mt[2][0] * vec->x + mt[2][1] * vec->y + mt[2][2] * vec->z + mt[2][3] * vec->w;
        result.w = mt[3][0] * vec->x + mt[3][1] * vec->y + mt[3][2] * vec->z + mt[3][3] * vec->w;

        return result;
    }

    
    
    
    transformation operator=(transformation &object) {
       for(int i = 0; i < 4; i++) {
           for(int j = 0; j < 4; j++) {
               mt[i][j] = object.mt[i][j];
               minvt[i][j] = object.minvt[i][j];
               int k = i+j;
           }
       }
       return *this;
   };
    
    bool operator==(const transformation &object) const {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if (mt[i][j] != object.mt[i][j])
                    return false;
                if (minvt[i][j] != object.minvt[i][j])
                    return false;
                int k = i+j;
            }
        }
        return true;
        // Return true if *this and rhs are equal, false otherwise
    }

    
    
    transformation& operator=(const transformation& object) {
        if (this == &object) {
                    return *this;
                }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                mt[i][j] = object.mt[i][j];
                minvt[i][j] = object.minvt[i][j];
                int k = i+j;
            }
        }
        return *this;
    }

    
    transformation operator+(const transformation& object) {
        transformation result;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                result.mt[i][j] = object.mt[i][j] + mt[i][j];
                result.minvt[i][j] = object.minvt[i][j] + minvt[i][j];
            }
        }
        return result;
    }

    transformation& operator+=(const transformation& object) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                mt[i][j] += object.mt[i][j];
                minvt[i][j] += object.minvt[i][j];
            }
        }
        return *this;
    }
    
    
    
    transformation operator*( const transformation &object)const {
        transformation result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result.mt[i][j] = 0;
                    result.minvt[i][j] = 0;
                    for (int k = 0; k < 4; k++) {
                        result.mt[i][j] += mt[i][k] * object.mt[k][j];
                        result.minvt[i][j] += minvt[i][k] * object.minvt[k][j];
                    }
                }
            }
            return result;
        }
    
    
    transformation* operator*(transformation& object) {
         transformation* result = new transformation;
         for (int i = 0; i < 4; i++) {
             for (int j = 0; j < 4; j++) {
                 result->mt[i][j] = 0;
                 result->minvt[i][j] = 0;
                 for (int k = 0; k < 4; k++) {
                     result->mt[i][j] += mt[i][k] * object.mt[k][j];
                     result->minvt[i][j] += minvt[i][k] * object.minvt[k][j];
                 }
             }
         }
        
        result->updateInverseTranpose();
         return result;
     }
    

    transformation& operator*=(const transformation& object)  {
        transformation result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.mt[i][j] = 0;
                //result.minvt[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.mt[i][j] += mt[i][k] * object.mt[k][j];
                   // result.minvt[i][j] += minvt[i][k] * object.minvt[k][j];
                }
            }
        }
        
        result.updateInverseTranpose();
        
        *this = result;
        return *this;
    }
    
    //for worldToCamera
    transformation operator^(matrix4 matrix4) const {
        transformation result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.mt[i][j] = 0;
                result.minvt[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.mt[i][j] += mt[i][k] * matrix4[k][j];
                    result.minvt[i][j] += minvt[i][k] * matrix4[k][j];
                }
            }
        }
        return result;
    }

    localGeo operator*(const localGeo currentLocalGeo) {
        localGeo a = currentLocalGeo;
        
        localGeo transformedLocalGeo;
        
        transformedLocalGeo.pos.x = currentLocalGeo.pos.x * mt[0][0] + currentLocalGeo.pos.y * mt[1][0] + currentLocalGeo.pos.z * mt[2][0];
        transformedLocalGeo.pos.y = currentLocalGeo.pos.x * mt[0][0] + currentLocalGeo.pos.y * mt[1][0] + currentLocalGeo.pos.z * mt[2][0];
        transformedLocalGeo.pos.z = currentLocalGeo.pos.x * mt[0][0] + currentLocalGeo.pos.y * mt[1][0] + currentLocalGeo.pos.z * mt[2][0];

        transformedLocalGeo.normal.x = currentLocalGeo.normal.x * mt[0][0] + currentLocalGeo.normal.y * mt[1][0] + transformedLocalGeo.normal.z * mt[2][0];
        transformedLocalGeo.normal.y = currentLocalGeo.normal.x * mt[0][0] + currentLocalGeo.normal.y * mt[1][0] + currentLocalGeo.normal.z * mt[2][0];
        transformedLocalGeo.normal.z = currentLocalGeo.normal.x * mt[0][0] + currentLocalGeo.normal.y * mt[1][0] + currentLocalGeo.normal.z * mt[2][0];
        
        return transformedLocalGeo;
    }
    
    //idk what this even does??? may be pointless???
    static matrix4 Transpose(const matrix4 &m) {
       return matrix4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
                        m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
                        m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
                        m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
        
    }
    
    //scaling
    template <typename Vec>
    void scaling(const vector3<Vec> &startVector) {
        
        
        mt[0][0] *= startVector.x;
        mt[1][1] *= startVector.y;
        mt[2][2] *= startVector.z;
        
        minvt[0][0] /= startVector.x;
        minvt[1][1] /= startVector.y;
        minvt[2][2] /= startVector.z;

    }
    //translation
    template <typename Vec>
    void translation(const vector3<Vec> &startVector) {
        
        matrix4 mt(1, 0, 0, startVector.x,
                  0, 1, 0, startVector.y,
                  0, 0, 1, startVector.z,
                  0, 0, 0,       1);
        matrix4 minv(1, 0, 0, -startVector.x,
                     0, 1, 0, -startVector.y,
                     0, 0, 1, -startVector.z,
                     0, 0, 0,        1);
        
        this->mt = mt;
        this->minvt = minv;
    }
    
    //rotation
    template <typename Vec>
    static transformation rotationX(const float &theta) {
        //rotationX
        float sinThetaX = std::sin(math::Radians(theta));
        float cosThetaX = std::cos(math::Radians(theta));
        matrix4 mt(1,         0,          0, 0,
                  0, cosThetaX, -sinThetaX, 0,
                  0, sinThetaX,  cosThetaX, 0,
                  0,         0,          0, 1);
        return transformation(mt, Transpose(mt));
    }
    
    template <typename Vec>
    static transformation rotationY(const float &theta) {
        float sinThetaY = std::sin(math::Radians(theta));
        float cosThetaY = std::cos(math::Radians(theta));
        matrix4 mt(cosThetaY,   0,  sinThetaY, 0,
                           0,   1,          0, 0,
                  -sinThetaY,   0,  cosThetaY, 0,
                           0,   0,          0, 1);
        
        return transformation(mt, Transpose(mt));
    }
    
    template <typename Vec>
    static transformation rotationZ(const float &theta) {
        float sinThetaZ = std::sin(math::Radians(theta));
        float cosThetaZ = std::cos(math::Radians(theta));
        matrix4 mt(cosThetaZ, -sinThetaZ, 0, 0,
                   sinThetaZ, cosThetaZ, 0, 0,
                    0, 0, 1, 0,
                    0,        0,         0, 1);
        return transformation(mt, Transpose(mt));
    }
    
    template <typename Vec>
    void rotation(float theta, const Vec &vector) {
        
        Vector3f a = normalize(vector);
        float sinTheta = std::sin(math::Radians(theta));
        float cosTheta = std::cos(math::Radians(theta));
        
        matrix4 X(1,         0,          0, 0,
                  0, cosTheta, -sinTheta, 0,
                  0, sinTheta,  cosTheta, 0,
                  0,         0,          0, 1);

        
        matrix4 Y(cosTheta,   0,  sinTheta, 0,
                  0,   1,          0, 0,
                  -sinTheta,   0,  cosTheta, 0,
                  0,   0,          0, 1);
        
        matrix4 Z(cosTheta, -sinTheta, 0, 0,
                   sinTheta, cosTheta, 0, 0,
                    0, 0, 1, 0,
                    0,        0,         0, 1);
        
        matrix4 m;
        // Compute rotation of first basis vector
        m.m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
        m.m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
        m.m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
        m.m[0][3] = 0;

        // Compute rotations of second and third basis vectors
        m.m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
        m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
        m.m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
        m.m[1][3] = 0;

        m.m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
        m.m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
        m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
        m.m[2][3] = 0;
                
        // Compute rotations of second and third basis vectors
        m.m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
        m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
        m.m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
        m.m[1][3] = 0;

        m.m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
        m.m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
        m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
        m.m[2][3] = 0;
             
        
        if (theta == 0 || a.x == a.y == a.z == 0) {
            // If theta is 0 or the input vector is (0, 0, 0, 0), return an identity matrix.
            this->mt = matrix4();
            this->minvt = matrix4();
            return;
        }
        
        this->mt = m;
        this->minvt = transformation::Transpose(inverse(m));
    }


    
    // Transformation of a vector
    template <typename V>
    vector3<V> operator*(const vector3<V>& v) const {
        matrix4 mt = this->mt;
        vector3<V> transformedVec;
        
        transformedVec.x = v.x * mt[0][0] + v.y * mt[1][0] + v.z * mt[2][0] + mt[3][0];
        transformedVec.y = v.x * mt[0][1] + v.y * mt[1][1] + v.z * mt[2][1] + mt[3][1];
        transformedVec.z = v.x * mt[0][2] + v.y * mt[1][2] + v.z * mt[2][2] + mt[3][2];
        
        return transformedVec;

    }
    
    template <typename V>
    vector4<V> operator*(const vector4<V>& v) const {
        matrix4 mt = this->mt;
        vector4<V> transformedVec;
        
        transformedVec.x = v.x * mt[0][0] + v.y * mt[1][0] + v.z * mt[2][0] + v.w * mt[3][0];
        transformedVec.y = v.x * mt[0][1] + v.y * mt[1][1] + v.z * mt[2][1] + v.w * mt[3][1];
        transformedVec.z = v.x * mt[0][2] + v.y * mt[1][2] + v.z * mt[2][2] + v.w * mt[3][2];
        transformedVec.w = v.x * mt[0][3] + v.y * mt[1][3] + v.z * mt[2][3] + v.w * mt[3][3];
        
        return transformedVec;
    }

    // Transformation of a ray
    ray operator*(const ray& currentRay) const {
        ray newRay= currentRay;
        transformation test = *this;
        
        //this is matrix vector multiplcation 
        //newRay.lookFrom = (test.minvt)*currentRay.lookFrom;
        //newRay.lookAt = (test.minvt)*currentRay.lookAt;
        
        //this is just calling opposite of what the actual math is
        newRay = (test.minvt)*currentRay;

        
        return newRay;
    }
    
    // Transformation of a normal
    template <typename N>
    normal<N> operator*(const normal<N>& n) const {
        // Apply transformation to n and return the transformed normal
        return minvt;
    }
    
    template <typename P>
    point3<P> operator*(const point3<P>& p) const {
        point3<P> result;  // Declare and initialize result as a point3<P> object
        for(int i = 0; i < 4; i++) {
            result[i] = 0;
            for(int j = 0; j < 3; j++) {
                
                result[i] += this->mt[i][j] * p[j];
            }
        }
        return result;
    }
    
    const matrix4 &getMat() const {
        return mt;
    }

    
    void updateInverseTranpose() {
        minvt = transformation::Transpose(inverse(mt));
    }

    
    matrix4 mt;
    matrix4 minvt;
  
};



class transformCache {
  public:
    transformCache()
        : hashTable(512), hashTableOccupancy(0) {}

    // TransformCache Public Methods
    transformation *lookup(const transformation &t);

    void clear();

  private:
    void insert(transformation *tNew);
    void grow();

    static uint64_t hash(const transformation &t) {
        const char *ptr = (const char *)(&t.getMat());
        size_t size = sizeof(matrix4);
        uint64_t hash = 14695981039346656037ull;
        while (size > 0) {
            hash ^= *ptr;
            hash *= 1099511628211ull;
            ++ptr;
            --size;
        }
        return hash;
    }

    // TransformCache Private Data
    //I need to change this to array
    std::vector<transformation *> hashTable;
    int hashTableOccupancy;
    memoryArena arena;
};

 //checks hash table
void insert(transformation *tNew);

//expand hashtable, if insert says its needed

void grow();


struct transformationSet {
    // TransformSet Public Methods
    transformation &operator[](int i) {
        return t[i];
    }
    const transformation &operator[](int i) const {
        return t[i];
    }
    
    //inverse for use in time??
    /*
    friend transformationSet inverse(const transformationSet &ts) {
        transformationSet tInv;
        for (int i = 0; i < maxTransforms; ++i) tInv.t[i] = inverse(ts.t[i]);
        return tInv;
    }
    */
    void PushTransform(const transformation& transform) {
        if (stackIndex >= maxTransforms) {
            throw std::overflow_error("Transformation stack overthrow.");
               return;
           }
        
            
            t[stackIndex++] = transform;
        
       }

    void PopTransform() {
           if (stackIndex <= 0) {
               //throw std::underflow_error("Transformation stack underflow.");
               return;
           }
           //--stackIndex;
       }

    /*
    bool IsAnimated() const {
        for (int i = 0; i < maxTransforms - 1; ++i)
            if (t[i] != t[i + 1]) return true;
        return false;
    }
     */
    int stackIndex = 0;

  private:
    transformation t[maxTransforms];

    
};


template <typename T>
point3<T> multPointMatrix(matrix4 &m, const point3<T> &in)
{
    point3<T> result;

    /*
    result.x = m[0][0] * in.x + m[1][0] * in.y + m[2][0] * in.z + m[3][0];
    result.y = m[0][1] * in.x + m[1][1] * in.y + m[2][1] * in.z + m[3][1];
    result.z = m[0][2] * in.x + m[1][2] * in.y + m[2][2] * in.z + m[3][2];
*/
    
    result.x   = in.x * m[0][0] + in.y * m[1][0] + in.z * m[2][0] + /* in.z = 1 */ m[3][0];
    result.y   = in.x * m[0][1] + in.y * m[1][1] + in.z * m[2][1] + /* in.z = 1 */ m[3][1];
    result.z   = in.x * m[0][2] + in.y * m[1][2] + in.z * m[2][2] + /* in.z = 1 */ m[3][2];
    float w = in.x * m[0][3] + in.y * m[1][3] + in.z * m[2][3] + /* in.z = 1 */  m[3][3];
    
    if (w != 1) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }
    
    return result;


}




/*

class matrixStackTransformations {
    void pushTransform(const matrix4 &transform) {
            if (transformStack.empty()) {
                transformStack.push(transform);
            } else {
                transformStack.push(transformStack.top() * transform);
            }
        }

        void popTransform() {
            if (!transformStack.empty()) {
                transformStack.pop();
            }
        }
    
    matrix4 transformStack;


};
*/

/*
class transformationStack {
private:
    std::stack<transformation> stack_;
    transformation current_;

public:
    transformationStack() {
        transformation current_;
    }

    void push() {
        stack_.push(current_);
    }

    void pop() {
        if (stack_.empty()) {
            throw std::runtime_error("Matrix stack is empty");
        }
        current_ = stack_.top();
        stack_.pop();
    }

    void loadIdentity() {
        transformation current_;
    }

    /*
    void translate(float x, float y, float z) {
        transformation current = transformation::translation(vector3(x, y, z));
        current_ *= current;
        //transformation current_ *= translate(current_, vector3(x, y, z));
    }

    void rotate(float angle, float x, float y, float z) {
        transformation transformationStackMatrix; //should be identity matrix

        transformation rotateMatrixX = transformation::rotationX(angle);
        transformation rotateMatrixY = transformation::rotationY(angle);
        transformation rotateMatrixZ = transformation::rotationZ(angle);

        transformation rotationMatrix = (rotateMatrixX * rotateMatrixY) * rotateMatrixZ;
        
        transformationStackMatrix *= rotationMatrix;// * transformationMatrix;

    }

    void scaling(float x, float y, float z) {
        transformation scaleMatrix = transformation::scaling(scale);
        transformationMatrix *= scaleMatrix;

        current_ = scaling(current_, vector3(x, y, z));
    }
    

    transformation getCurrentTransformation() const {
        return current_;
    }
};

 */

//transformationSet transformationStack;

#endif /* transform_hpp */


/*
 Support Point, Vector, Normal, Ray, LocalGeo transformation by
 operator * overloading
 */


