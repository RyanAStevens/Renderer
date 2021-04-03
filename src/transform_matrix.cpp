#include <transform_matrix.h>
#include <cstdio>

TransformMatrix::TransformMatrix() : Matrix(IDENTITY)
{
//    printf("hello from default TransformMatrix constructor\n");
}

TransformMatrix::TransformMatrix(enum matrix_constructor_t mat_type) : Matrix(mat_type)
{
 //   printf("hello from TransformMatrix matrix_constructor_t constructor\n");
}

TransformMatrix::TransformMatrix(int n_r, int n_c) : Matrix(n_r, n_c)
{
  //  printf("hello from TransformMatrix (row, col) constructor\n");
}

TransformMatrix::TransformMatrix(const TransformMatrix& tm) : Matrix(IDENTITY)
{
 //   printf("hello from TransformMatrix copy constructor\n");
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            (*(this->data))[row][col] = (*(tm.data))[row][col];
        }
    }
}
/*
*/

TransformMatrix::TransformMatrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
   // printf("hello from TransformMatrix(Vector3H) constructor\n");
    this->data->push_back(r0);
    this->data->push_back(r1);
    this->data->push_back(r2);
    this->data->push_back(r3);
}

TransformMatrix::~TransformMatrix()
{
}


TransformMatrix TransformMatrix::operator*(TransformMatrix rhs)
{
    TransformMatrix ret;
    
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
    return ret;
}

Vertex TransformMatrix::operator*(Vertex rhs)
{
    Vertex ret;
    int l = n_rows;
    int m = n_cols;
    float sum = 0;
    for(int row = 0; row < l; row++)
    {
           sum = 0;
           for(int i = 0; i < m; i++)
           {
               sum += (*(this->data))[row][i] * rhs.components[i];
           }
           ret.components[row] = sum;
    }
    return ret;
}
