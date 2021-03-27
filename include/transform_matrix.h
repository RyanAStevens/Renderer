#ifndef TRANSFORM_MATRIX_H_
#define TRANSFORM_MATRIX_H_

#include <vector3h.h>
#include <matrix.h>

class TransformMatrix : public Matrix
{
public:
    TransformMatrix();
    TransformMatrix(int n_r, int n_c);
    TransformMatrix(enum matrix_constructor_t mat_type);
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();
//    TransformMatrix operator*(const TransformMatrix& rhs);
//    Matrix operator*(const Matrix& rhs);
//    TransformMatrix operator=(const TransformMatrix& rhs);
template <class T>
T mult(T rhs)
{
    printf("hello from mult\n");
    //initialize the return matrix
    T ret(n_cols, rhs.n_rows);
    
    //number of columns in lhs must match number of columns in rhs
    printf("n_cols = %d rhs.n_rows = %d\n", n_cols, rhs.n_rows);
    if( n_cols == rhs.n_rows)
    {
        //A(l x m) * B(m x n) = C(l x n)
        int l = n_rows;
        int m = n_cols;
        int n = rhs.n_cols; 
        float sum = 0;
        for(int row = 0; row < l; row++)
        {
           for(int col = 0; col < n; col++)
           {
               sum = 0;
               for(int i = 0; i < m; i++)
               {
                   sum += (*(this->data))[row][i] * (*rhs.data)[i][col];
               }
               (*ret.data)[row][col] = sum;
           }
        }
    }
    else
    {
        printf("these matrices cannot be multiplied. size mismatch\n");
    }
    return ret;
}

TransformMatrix operator*(TransformMatrix rhs);
};

#endif //TRANSFORM_MATRIX_H_
