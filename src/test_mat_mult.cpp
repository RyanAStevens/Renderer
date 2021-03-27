#include "../include/transform_matrix.h"
#include <stdio.h>

int main()
{
    TransformMatrix A;
    A.print();
    TransformMatrix B(INVERT_Y);
    B.print();
    TransformMatrix C(INVERT_X);
    C.print();
    (A*B*C).print();
}
