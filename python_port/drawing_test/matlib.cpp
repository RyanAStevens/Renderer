/* Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;
*/

// Matrix Stack Library -- My code from Project 1A

#include <math.h>

typedef std::vector<float> matrix_row;
typedef std::vector<matrix_row> matrix;
typedef std::vector<matrix> matrix_stack;

// my own matrix multiplication function
matrix matrix_mult(A, B)
{
    //check for proper input
    if(A.front().size() != B.size())
    {
        printf("Error: Number of columns in A must match number of rows in B");
        return -1;
    }
    
    //A(l x m) * B(m x n) = C(l x n)
    float l = A.size();
    float n = B.front().size();
    float m = B.size();
    
    //initialize the return matrix
    matrix product_matrix(A.size(), matrix_row(B.front().size(), 0.0f));
    
    //perform multiplication
    index = 0;
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

void gtInitialize()
{
    // initialize stack with a single 4x4 identity matrix
    matrix_stack = {{{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}};
}

void gtPushMatrix()
{
    //copy top of stack and push onto stack
    matrix_stack.push_back(matrix_stack.back());
}

void gtPopMatrix()
{
    // check to see if stack can be popped
    if(matrix_stack.size() > 1)
    {
        matrix_stack.pop_back();
    }
    else
    {
        printf("cannot pop the matrix stack\n");
    }
}

void gtTranslate(x, y, z)
{
    // create translation matrix
    T = {{1,0,0,x}, {0,1,0,y}, {0,0,1,z}, {0,0,0,1}};
    
    //multiply by CTM
    matrix_stack.back() = matrix_mult(matrix_stack.back(), T);
}

void gtScale(x, y, z)
{
    // create scale matrix
    S = [[x,0,0,0], [0,y,0,0], [0,0,z,0], [0,0,0,1]];

    //multiply by CTM
    matrix_stack.back() = matrix_mult(matrix_stack.back(), S);
}

void gtRotateX(theta)
{
    // create rotation matrix
    Rx = [[1,0,0,0], [0,cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0], [0,sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0], [0,0,0,1]];

    //multiply Rx by CTM
    matrix_stack.back() = matrix_mult(matrix_stack.back(), Rx);
}

void gtRotateY(theta)
{
    // create rotation matrix
    Ry = {{cos(theta*M_PI/180.0),0,sin(theta*M_PI/180.0),0}, {0,1,0,0}, {-sin(theta*M_PI/180.0),0,cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply by CTM
    matrix_stack.back() = matrix_mult(matrix_stack.back(), Ry);
}

void gtRotateZ(theta)
{
    // create rotation matrix
    Rz = {{cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0,0}, {sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0,0}, {0,0,1,0}, {0,0,0,1}};

    //multiply by CTM
    matrix_stack.back() = matrix_mult(matrix_stack.back(), Rz);
}
