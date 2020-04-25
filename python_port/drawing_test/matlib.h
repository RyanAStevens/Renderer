/* Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;
*/

// Matrix Stack Library -- My code from Project 1A

#include <math.h>

typedef std::vector<float> matrix_row;
typedef std::vector<matrix_row> matrix;
typedef std::vector<matrix> matrix_stack;

class MatLib
{
public:
        matrix_stack mat_stack;
        matrix matrix_mult(A, B);
        void gtInitialize();
        void gtPushMatrix();
        void gtPopMatrix();
        void gtTranslate(x, y, z);
        void gtScale(x, y, z);
        void gtRotateX(theta);
        void gtRotateY(theta);
        void gtRotateZ(theta);
};
