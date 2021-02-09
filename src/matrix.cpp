/*  
    Ryan Stevens
    CS 3451 Computer Graphics
    Georgia Institute of Technology
    Spring 2017

    file: matlib.cpp
*/

// Matrix Stack Library -- My code from Project 1A

#include <math.h>
#include <matrix.h>
#include <stdio.h>
#include <stack_trace.h>

Matrix::Matrix()
{
    data = new std::vector<Vector3H>;
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    (*data)[0][0] = 1.0;
    (*data)[1][1] = 1.0;
    (*data)[2][2] = 1.0;
    (*data)[3][3] = 1.0;
}

Matrix::Matrix(int n_columns)
{
   
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < n_columns; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
}

Matrix::Matrix(matrix_constructor_t id)
{
    data = new std::vector<Vector3H>;
    
    switch(id)
    {
        case IDENTITY:
            for(int i = 0; i < 4; i++)
            {
                Vector3H column;
                data->push_back(column);
            }
            (*data)[0][0] = 1.0;
            (*data)[1][1] = 1.0;
            (*data)[2][2] = 1.0;
            (*data)[3][3] = 1.0;
            break;
        default:
            ;
    }
    
}

Matrix::Matrix(Vector3H r0, Vector3H r1, Vector3H r2, Vector3H r3)
{
    data = new std::vector<Vector3H>;
   
    data->push_back(r0);
    data->push_back(r1);
    data->push_back(r2);
    data->push_back(r3);
}

Matrix::Matrix(double x_in, double y_in, double z_in)
{
    data = new std::vector<Vector3H>;
    
    Vector3H vertex;

    vertex[0] = x_in;
    vertex[1] = y_in;
    vertex[2] = z_in;
    vertex[3] = 1.0;

    data->push_back(vertex);
}

Matrix::~Matrix()
{
}

void Matrix::print()
{
    for(int column = 0; column < data->size(); column++)
    {   
        printf("| ");
        for(int row = 0; row < 4; row++)
        {
            printf("%5.2f ", (*data)[column][row]);
        }
        printf("|\n");
    }
}

Matrix& Matrix::operator=(Matrix rhs)
{
    if(rhs.data->size() == data->size())
    {
            std::vector<Vector3H>::iterator it_i_orig;
            std::vector<Vector3H>::iterator it_i_dest;
            for(it_i_orig = rhs.data->begin(), it_i_dest = data->begin(); (it_i_orig != rhs.data->end()) || (it_i_dest != data->end()); ++it_i_orig, ++it_i_dest)
            {
                for(int row = 0; row < 4; row++)
                {
                    (*it_i_dest)[row] = (*it_i_orig)[row];
                }
            }
    }
    else
    {
        printf("ERROR: cannot assign. matrix size mismatch\n");
    }

	return *this;
}

Matrix Matrix::operator*(Matrix rhs)
{
    //A(l x m) * B(m x n) = C(l x n)
    int l = (this->data)->size();
    int m = rhs.data->size();
    int n = 4;
    //initialize the return matrix
    Matrix ret(l);
    
        float sum = 0;
        for(int row = 0; row < l; row++)
        {
           for(int col = 0; col < n; col++)
           {
               sum = 0;
               for(int i = 0; i < m; i++)
               {
                   sum += (*data)[row][i] * (*rhs.data)[i][col];
               }
               (*ret.data)[row][col] = sum;
           }
        }
        return ret;
}

Vector3H& Matrix::operator[](int i)
{
    return (*data)[i];
}   
