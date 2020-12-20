#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include <vector3h.h>
#include <matrix.h>

#define NUM_ROWS 4
#define NUM_COMPS 4

class TransformMatrix{
public:
    TransformMatrix();
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();
    TransformMatrix operator*(const TransformMatrix& rhs);
    Matrix operator*(const Matrix& rhs);
    TransformMatrix operator=(const TransformMatrix& rhs);
    Vector3H  row[4];
};

#endif //TRANSFORM_MATRIX_H_
