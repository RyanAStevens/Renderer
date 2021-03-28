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

Matrix::Matrix(int n_r, int n_c) : n_rows(n_r), n_cols(n_c)
{
    //keeping n_r as an input for possible future implementation where 
    //#rows might be something other than 4(Vector3H has 4 elements)
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < n_c; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
}

Matrix::Matrix(matrix_constructor_t id)
{
    n_rows = 4;
    data = new std::vector<Vector3H>;
    
    for(int i = 0; i < 4; i++)
    {
        Vector3H column;
        data->push_back(column);
    }
    
    switch(id)
    {
        case IDENTITY:
            n_cols = 4;
            (*data)[0][0] = 1.0;
            (*data)[1][1] = 1.0;
            (*data)[2][2] = 1.0;
            (*data)[3][3] = 1.0;
            break;
        case INVERT_X:
            n_cols = 4;
            (*data)[0][0] = -1.0;
            (*data)[1][1] = 1.0;
            (*data)[2][2] = 1.0;
            (*data)[3][3] = 1.0;
            break;
        case INVERT_Y:
            n_cols = 4;
            (*data)[0][0] = 1.0;
            (*data)[1][1] = -1.0;
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

Vector3H& Matrix::operator[](int i)
{
    return (*data)[i];
}   
