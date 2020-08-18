/*  
    Ryan Stevens
    CS 3451 Computer Graphics
    Georgia Institute of Technology
    Spring 2017

    file: matlib.cpp
*/

// Matrix Stack Library -- My code from Project 1A

#include <math.h>
#include <matlib.h>
#include <stdio.h>

Matrix::Matrix()
{
    for(int i = 0; i < 4; i++)
    {
	    data.emplace_back(4, 0.0f);
    }
}

Matrix::~Matrix()
{
}

Matrix::print()
{
}

Matrix& operator=(Matrix& rhs)
{
    std::vector<double>>::iterator it_i_dest
    std::vector<double>>::iterator it_i_orig
    std::vector<double>::iterator it_j_dest
    std::vector<double>::iterator it_j_orig 
    for(it_i_orig = rhs.data.begin(), it_i_dest = this->data.begin(); it_i_orig != rhs.data.end(), it_i_dest = this->data.end(); ++it_i_orig, ++it_i_dest)
    {
        for(it_j_orig = *it_i_orig.begin(), it_j_dest= *it_i_dest.begin(); it_j_orig != *it_i_orig.end(), it_j_dest != *it_i_dest.end(); ++it_j_orig, ++it_j_dest)
        {
            
        }
    }
}

std::vector<double>& Matrix::operator[](int i)
{
    return this->data[i];
}

Matrix MatLib::matrix_mult(Matrix A, Matrix B)
{
    printf("hello from matrix_mult\n");
    //A(l x m) * B(m x n) = C(l x n)
    int l = A.size();
    printf("l = %d\n", l);
    int n = B.front().size();
    printf("n = %d\n", n);
    int m = B.size();
    printf("m = %d\n", m);
    
    //initialize the return matrix
    Matrix product_matrix(A.size(), matrix_row(B.front().size(), 0.0f));
    printf("matrix_mult: 1\n");
    
    //check for proper input
    if(A.front().size() != B.size())
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return product_matrix;
    }
    printf("matrix_mult: 2\n");
    
    //perform multiplication
    int index = 0;
    for(int i = 0; i < l; i++)
    {
        printf("i = %d\n", i);
        for(int j = 0; j < n; j++)
        {
        printf("j = %d\n", j);
            for(int k = 0; k < m; k++)
            {
        printf("k = %d\n", k);
                printf("matrix_mult: %f + (%f * %f)\n", product_matrix[index/n][index%n], A[i][k], B[k][j]);
                product_matrix[index/n][index%n] = product_matrix[index/n][index%n] + (A[i][k] * B[k][j]);
            }
            index = index + 1;
        }
    }
    return product_matrix;
}

void MatLib::gtInitialize()
{
    // initialize stack with a single 4x4 identity matrix

    this->mat_stack.clear();
    this->mat_stack = {{{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}};
}

void MatLib::gtPushMatrix()
{
    //copy top of stack and push onto stack
    this->mat_stack.push_back(this->mat_stack.back());
}

void MatLib::gtPopMatrix()
{
    // check to see if stack can be popped
    if(this->mat_stack.size() > 1)
    {
        this->mat_stack.pop_back();
    }
    else
    {
        printf("cannot pop the matrix stack\n");
    }
}

void MatLib::gtTranslate(double x, double y, double z)
{
    // create translation matrix
    Matrix T = {{1,0,0,x}, {0,1,0,y}, {0,0,1,z}, {0,0,0,1}};
    
    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), T);
}

void MatLib::gtScale(double x, double y, double z)
{
    // create scale matrix
    Matrix S = {{x,0,0,0}, {0,y,0,0}, {0,0,z,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), S);
}

void MatLib::gtRotateX(double theta)
{
    // create rotation matrix
    Matrix Rx = {{1,0,0,0}, {0,cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0}, {0,sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply Rx by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Rx);
}

void MatLib::gtRotateY(double theta)
{
    // create rotation matrix
    Matrix Ry = {{cos(theta*M_PI/180.0),0,sin(theta*M_PI/180.0),0}, {0,1,0,0}, {-sin(theta*M_PI/180.0),0,cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Ry);
}

void MatLib::gtRotateZ(double theta)
{
    // create rotation matrix
    Matrix Rz = {{cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0,0}, {sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0,0}, {0,0,1,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Rz);
}
