#include <transform_matrix.h>
#include <stdio.h>

int main()
{
    TransformMatrix A;
    A.print();
    TransformMatrix B(INVERT_Y);
    B.print();
    TransformMatrix C(INVERT_X);
    C.print();
    Vertex D(1.0, 2.0, 3.0);
    D.print();
    (A*B*C*D).print();
    return 0;
}
