#include <transform_matrix.h>
#include <cstdio>

TransformMatrix::TransformMatrix() : Matrix(IDENTITY)
{
    printf("hello from default TransformMatrix constructor\n");
}

TransformMatrix::TransformMatrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
    printf("hello from TransformMatrix(Vector3H) constructor\n");
    data->push_back(r0);
    data->push_back(r1);
    data->push_back(r2);
    data->push_back(r3);
}

TransformMatrix::~TransformMatrix()
{
}
