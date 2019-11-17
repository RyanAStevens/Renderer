#include <transform_matrix.h>

Transform_Matrix::Transform_Matrix()
{
        this->row[0] = Vector3H(1, 0, 0, 0);
        this->row[1] = Vector3H(0, 1, 0, 0);
        this->row[2] = Vector3H(0, 0, 1, 0);
        this->row[3] = Vector3H(0, 0, 0, 1);
}

Transform_Matrix::Transform_Matrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
        this->row[0] = r0;
        this->row[1] = r1;
        this->row[2] = r2;
        this->row[3] = r3;
}

Transform_Matrix::~Transform_Matrix()
{
}

Transform_Matrix Transform_Matrix::operator*(const Transform_Matrix& rhs)
{
        float sum = 0;
        Transform_Matrix ret = Transform_Matrix();
        for(int row = 0; row < 4; row++)
        {
           for(int col = 0; col < 4; col++)
           {
               sum = 0;
               for(int i = 0; i < 4; i++)
               {
                   //ret[row][col] = A[row][i]*B[i][col]
                   sum += this->row[row].components[i] * rhs.row[i].components[col];
               }
               ret.row[row].components[col] = sum;
           }
        }
        return ret;
}
