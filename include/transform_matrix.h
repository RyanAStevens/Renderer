#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include <vector3h.h>
#include <matrix.h>

class TransformMatrix : public Matrix
{
public:
    TransformMatrix();
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();
//    TransformMatrix operator*(const TransformMatrix& rhs);
//    Matrix operator*(const Matrix& rhs);
//    TransformMatrix operator=(const TransformMatrix& rhs);
};

#endif //TRANSFORM_MATRIX_H_
