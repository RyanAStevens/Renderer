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

matrix MatLib::matrix_mult(matrix A, matrix B)
{
    
    //A(l x m) * B(m x n) = C(l x n)
    int l = A.size();
    int n = B.front().size();
    int m = B.size();
    
    //initialize the return matrix
    matrix product_matrix(A.size(), matrix_row(B.front().size(), 0.0f));
    
    //check for proper input
    if(A.front().size() != B.size())
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return product_matrix;
    }
    
    //perform multiplication
    int index = 0;
    for(int i = 0; i <= l; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            for(int k = 0; k <= m; k++)
            {
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
    matrix T = {{1,0,0,x}, {0,1,0,y}, {0,0,1,z}, {0,0,0,1}};
    
    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), T);
}

void MatLib::gtScale(double x, double y, double z)
{
    // create scale matrix
    matrix S = {{x,0,0,0}, {0,y,0,0}, {0,0,z,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), S);
}

void MatLib::gtRotateX(double theta)
{
    // create rotation matrix
    matrix Rx = {{1,0,0,0}, {0,cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0}, {0,sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply Rx by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Rx);
}

void MatLib::gtRotateY(double theta)
{
    // create rotation matrix
    matrix Ry = {{cos(theta*M_PI/180.0),0,sin(theta*M_PI/180.0),0}, {0,1,0,0}, {-sin(theta*M_PI/180.0),0,cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Ry);
}

void MatLib::gtRotateZ(double theta)
{
    // create rotation matrix
    matrix Rz = {{cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0,0}, {sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0,0}, {0,0,1,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.back() = matrix_mult(this->mat_stack.back(), Rz);
}
