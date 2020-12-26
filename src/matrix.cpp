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

Matrix::Matrix(matrix_constructor_t id)
{
    printf("hello from Matrix(matrix_constructor_t id)\n");
    switch(id)
    {
        case IDENTITY:
            for(int i = 0; i < 4; i++)
            {
                std::vector<double> row(4, 0.0);
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

Matrix::Matrix(int n_rows, int n_cols)
{
    data = new std::vector<std::vector<double> >;
    for(int i = 0; i < n_rows; i++)
    {   
        std::vector<double> row(n_cols, 0.0);
        data->push_back(row);
    }
}

Matrix::Matrix(double x_in, double y_in, double z_in)
{
    std::vector<double> x (1, x_in);
    std::vector<double> y (1, y_in);
    std::vector<double> z (1, z_in);
    std::vector<double> h (1, 1.0);
    
    data = new std::vector<std::vector<double> >;
    
    data->push_back(x);
    data->push_back(y);
    data->push_back(z);
    data->push_back(h);
}

Matrix::~Matrix()
{
}

void Matrix::print()
{
    std::vector<std::vector<double> >::iterator it_i;
    std::vector<double>::iterator it_j;
    for(it_i = data->begin(); it_i != data->end(); ++it_i)
    {   
        printf("| ");
        for(it_j = it_i->begin(); it_j != it_i->end(); ++it_j)
        {
            printf("%5.2f ", *it_j);
        }
        printf("|\n");
    }
}

Matrix Matrix::operator=(Matrix rhs)
{
    std::vector<std::vector<double> >::iterator it_i_orig;
    std::vector<std::vector<double> >::iterator it_i_dest;
    std::vector<double>::iterator it_j_orig;
    std::vector<double>::iterator it_j_dest;
    for(it_i_orig = rhs.data->begin(), it_i_dest = data->begin(); (it_i_orig != rhs.data->end()) || (it_i_dest != data->end()); ++it_i_orig, ++it_i_dest)
    {
        for(it_j_orig = (*it_i_orig).begin(), it_j_dest= (*it_i_dest).begin(); (it_j_orig != (*it_i_orig).end()) || (it_j_dest != (*it_i_dest).end()); ++it_j_orig, ++it_j_dest)
        {
            *it_j_dest = *it_j_orig;
        }
    }

	return *this;
}


Matrix Matrix::operator*(Matrix rhs)
{
    //A(l x m) * B(m x n) = C(l x n)
    int l = data->size();
    int n = rhs.data->front().size();
    int m = rhs.data->size();

    //initialize the return matrix
    Matrix product_matrix(l, n);
    
    //check for proper input
    if(data->front().size() != rhs.data->size())
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return product_matrix;
    }
  //  printf("Matrix::operator*: 2\n");
    
    //perform multiplication
    int index = 0;
    for(int i = 0; i < l; i++)
    {
       // printf("i = %d\n", i);
        for(int j = 0; j < n; j++)
        {
       // printf("j = %d\n", j);
            for(int k = 0; k < m; k++)
            {
       // printf("k = %d\n", k);
                product_matrix[index/n][index%n] = product_matrix[index/n][index%n] + ((*data)[i][k] * rhs[k][j]);
            }
            index = index + 1;
        }
    }
   // printf("goodbye from Matrix::operator*\n");
    return product_matrix;
}

std::vector<double>& Matrix::operator[](int i)
{
    return (*data)[i];
}   
