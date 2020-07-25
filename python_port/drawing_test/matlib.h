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

class Matrix
{
    Matrix();
    ~Matrix();
    std::vector<std::vector<double>> data(4);
    void print();
}

typedef std::vector<matrix> matrix_stack;

class MatLib
{
public:
        matrix_stack mat_stack;
        matrix matrix_mult(matrix A, matrix B);
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
