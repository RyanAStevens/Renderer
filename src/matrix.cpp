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
    printf("hello from default Matrix constructor\n");
    data = new std::vector<Vector3H>;
}

Matrix::Matrix(int num_rows)
{
    printf("hello from Matrix(int num_rows)\n");
   
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < num_rows; i++)
    {
        Vector3H row;
        data->push_back(row);
    }
}

Matrix::Matrix(matrix_constructor_t id)
{
    printf("hello from Matrix(matrix_constructor_t id)\n");
   
    data = new std::vector<Vector3H>;
    
    switch(id)
    {
        case IDENTITY:
            for(int i = 0; i < 4; i++)
            {
                Vector3H row;
                data->push_back(row);
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

Matrix::Matrix(double x_in, double y_in, double z_in)
{
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H row;
        data->push_back(row);
    }
    
    (*data)[0][0] = x_in;
    (*data)[1][1] = y_in;
    (*data)[2][2] = z_in;
    (*data)[3][3] = 1.0;
}

Matrix::~Matrix()
{
}

void Matrix::print()
{
    std::vector<Vector3H>::iterator row;
    for(row = data->begin(); row != data->end(); ++row)
    {   
        printf("| ");
        for(int col = 0; col < 4; col++)
        {
            printf("%5.2f ", (*row)[col]);
        }
        printf("|\n");
    }
}

Matrix Matrix::operator=(Matrix rhs)
{
    std::vector<Vector3H>::iterator it_i_orig;
    std::vector<Vector3H>::iterator it_i_dest;
    for(it_i_orig = rhs.data->begin(), it_i_dest = data->begin(); (it_i_orig != rhs.data->end()) || (it_i_dest != data->end()); ++it_i_orig, ++it_i_dest)
    {
        for(int col = 0; col < 4; col++)
        {
            (*it_i_dest)[col] = (*it_i_orig)[col];
        }
    }

	return *this;
}

Matrix Matrix::operator*(Matrix rhs)
{
    //A(l x m) * B(m x n) = C(l x n)
    int l = data->size();
    int n = 4;
    int m = rhs.data->size();

    //initialize the return matrix
    Matrix ret(l);
    
    //check for proper input
    if(4 != m)
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return ret;
    }
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
