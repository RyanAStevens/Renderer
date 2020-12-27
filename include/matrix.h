#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <vector3h.h>
#include <vector>

enum matrix_constructor_t
{
   IDENTITY 
};

class Matrix
{
public:
    Matrix();
    Matrix(matrix_constructor_t id);
    Matrix(int num_rows);
    Matrix(int n_rows, int n_cols);
    Matrix(double x_in, double y_in, double z_in);
    ~Matrix();

    Matrix operator*(Matrix rhs);
    Matrix operator=(Matrix rhs);
    Vector3H& operator[](int i);
    
    void print();
    
    std::vector<Vector3H>* data;
};

#endif //MATRIX_H_
