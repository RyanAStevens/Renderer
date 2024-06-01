#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include <vector3h.h>
#include <vertex.h>
#include <math.h>
#include <vector>

enum matrix_constructor_t
{
   IDENTITY,
   SCALE,
   SCALE_X,
   SCALE_Y,
   SCALE_Z,
   TRANSLATE,
   TRANSLATE_X,
   TRANSLATE_Y,
   TRANSLATE_Z,
   ROTATE_X,
   ROTATE_Y,
   ROTATE_Z,
   INVERT_X,
   INVERT_Y
};

class TransformMatrix
{
public:
    TransformMatrix();
    TransformMatrix(int win_width, int win_height);
    TransformMatrix(const TransformMatrix& tm);
    TransformMatrix(enum matrix_constructor_t mat_type);
    TransformMatrix(enum matrix_constructor_t mat_type, double x_val, double y_val, double z_val);
    TransformMatrix(enum matrix_constructor_t mat_type, double val);
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();
    TransformMatrix operator*(TransformMatrix rhs);
    Vertex operator*(Vertex rhs);
    TransformMatrix& operator=(TransformMatrix rhs);
    Vector3H& operator[](int i);
    void print();
    std::vector<Vector3H>* data;
};

#endif //TRANSFORM_MATRIX_H_
