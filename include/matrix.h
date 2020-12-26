#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <vector>

enum matrix_constructor_t
{
   IDENTITY 
};

class Matrix
{
public:
    Matrix(matrix_constructor_t id);
    Matrix(int n_rows, int n_cols);
    Matrix(double x_in, double y_in, double z_in);
    ~Matrix();
    std::vector<Vector3H>* data;
    void print();
    Matrix operator*(Matrix rhs);
    Matrix operator=(Matrix rhs);
};

#endif //MATRIX_H_
