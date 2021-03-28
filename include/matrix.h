#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <vector3h.h>
#include <vector>

enum matrix_constructor_t
{
   IDENTITY,
   INVERT_X,
   INVERT_Y,
   VERTEX
};

class Matrix
{
public:
    Matrix();
    Matrix(matrix_constructor_t id);
    Matrix(int n_r, int n_c);
    Matrix(Vector3H, Vector3H, Vector3H, Vector3H);
    Matrix(double x_in, double y_in, double z_in);
    ~Matrix();

    Matrix operator*(Matrix rhs);
    Matrix& operator=(Matrix rhs);
    Vector3H& operator[](int i);
    
    void print();
    
    std::vector<Vector3H>* data;
    int n_rows;
    int n_cols;
};

#endif //MATRIX_H_
