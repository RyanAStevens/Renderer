#ifndef MATLIB_H_
#define MATLIB_H_

/* Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;
*/

// Matrix Stack Library -- My code from Project 1A

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
    std::vector<std::vector<double>> data;
    void print();
    std::vector<double>& operator[](int i);
    Matrix operator*(Matrix rhs);
    Matrix operator=(Matrix rhs);
};

typedef std::vector<Matrix> matrix_stack;

class MatLib
{
public:
        matrix_stack mat_stack;
        void gtInitialize();
        void gtPushMatrix();
        void gtPopMatrix();
        void gtTranslate(double x, double y, double z);
        void gtScale(double x, double y, double z);
        void gtRotateX(double theta);
        void gtRotateY(double theta);
        void gtRotateZ(double theta);
};

#endif //MATLIB_H_
