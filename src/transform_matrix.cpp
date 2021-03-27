#include <transform_matrix.h>
#include <cstdio>

TransformMatrix::TransformMatrix() : Matrix(IDENTITY)
{
    printf("hello from default TransformMatrix constructor\n");
}

TransformMatrix::TransformMatrix(enum matrix_constructor_t mat_type) : Matrix(mat_type)
{
    printf("hello from TransformMatrix matrix_constructor_t constructor\n");
}

TransformMatrix::TransformMatrix(int n_r, int n_c) : Matrix(n_r, n_c)
{
    printf("hello from TransformMatrix (row, col) constructor\n");
}

TransformMatrix::TransformMatrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
    printf("hello from TransformMatrix(Vector3H) constructor\n");
    this->data->push_back(r0);
    this->data->push_back(r1);
    this->data->push_back(r2);
    this->data->push_back(r3);
}

TransformMatrix::~TransformMatrix()
{
}


TransformMatrix TransformMatrix::operator*(TransformMatrix rhs)
{
    return this->mult<TransformMatrix>(rhs);
}
/*
Vertex TransformMatrix::operator*(Vertex rhs)
{
    return this->mult<Vertex>(rhs);
}
*/
