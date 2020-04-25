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

typedef std::vector<float> matrix_row;
typedef std::vector<matrix_row> matrix;
typedef std::vector<matrix> matrix_stack;

class MatLib
{
public:
        matrix_stack mat_stack;
        matrix matrix_mult(matrix A, matrix B);
        void gtInitialize();
        void gtPushMatrix();
        void gtPopMatrix();
        void gtTranslate(float x, float y, float z);
        void gtScale(float x, float y, float z);
        void gtRotateX(float theta);
        void gtRotateY(float theta);
        void gtRotateZ(float theta);
};

#endif //MATLIB_H_
