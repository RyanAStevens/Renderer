#include <transform_matrix.h>

TransformMatrix::TransformMatrix()
{
        this->row[0] = Vector3H(1, 0, 0, 0);
        this->row[1] = Vector3H(0, 1, 0, 0);
        this->row[2] = Vector3H(0, 0, 1, 0);
        this->row[3] = Vector3H(0, 0, 0, 1);
}

TransformMatrix::TransformMatrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
        this->row[0] = r0;
        this->row[1] = r1;
        this->row[2] = r2;
        this->row[3] = r3;
}

TransformMatrix::~TransformMatrix()
{
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix& rhs)
{
        float sum = 0;
        TransformMatrix ret = TransformMatrix();
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

TransformMatrix TransformMatrix::operator=(const TransformMatrix& rhs)
{
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            this->row[r].components[c] = rhs.row[r].components[c];
        }
    }
}
