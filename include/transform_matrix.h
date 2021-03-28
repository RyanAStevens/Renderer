#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include <vector3h.h>
#include <matrix.h>
#include <vertex.h>

class TransformMatrix : public Matrix
{
public:
    TransformMatrix();
    TransformMatrix(int n_r, int n_c);
    TransformMatrix(enum matrix_constructor_t mat_type);
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();


TransformMatrix operator*(TransformMatrix rhs);
Vertex operator*(Vertex rhs);
};

#endif //TRANSFORM_MATRIX_H_
