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

Matrix::Matrix(matrix_constructor_t id)
{
    switch(id)
    {
        case IDENTITY:
            for(int i = 0; i < 4; i++)
            {
                data.emplace_back(4, 0.0f);
            }
            break;
        default:
            ;
    }
    
}

Matrix::Matrix(int n_rows, int n_cols)
{
    for(int i = 0; i < n_rows; i++)
    {
	    data.emplace_back(n_cols, 0.0f);
    }
}

Matrix::Matrix(double x_in, double y_in, double z_in)
{
    std::vector<double> x(x_in);
    std::vector<double> y(y_in);
    std::vector<double> z(z_in);
    std::vector<double> h(1.0);
    
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(h);
}

Matrix::~Matrix()
{
}

void Matrix::print()
{
	
}

Matrix Matrix::operator=(Matrix rhs)
{
    std::vector<std::vector<double>>::iterator it_i_orig;
    std::vector<std::vector<double>>::iterator it_i_dest;
    std::vector<double>::iterator it_j_orig;
    std::vector<double>::iterator it_j_dest;
    for(it_i_orig = rhs.data.begin(), it_i_dest = this->data.begin(); it_i_orig != rhs.data.end(), it_i_dest != this->data.end(); ++it_i_orig, ++it_i_dest)
    {
        for(it_j_orig = (*it_i_orig).begin(), it_j_dest= (*it_i_dest).begin(); it_j_orig != (*it_i_orig).end(), it_j_dest != (*it_i_dest).end(); ++it_j_orig, ++it_j_dest)
        {
            *it_j_dest = *it_j_orig;
        }
    }

	return *this;
}


Matrix Matrix::operator*(Matrix rhs)
{
    printf("hello from matrix_mult\n");
    //A(l x m) * B(m x n) = C(l x n)
    int l = this->data.size();
    printf("l = %d\n", l);
    int n = rhs.data.front().size();
    printf("n = %d\n", n);
    int m = rhs.data.size();
    printf("m = %d\n", m);
    
    //initialize the return matrix
    Matrix product_matrix(l, n);
    printf("matrix_mult: 1\n");
    
    //check for proper input
    if(this->data.front().size() != rhs.data.size())
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
                printf("matrix_mult: %f + (%f * %f)\n", product_matrix[index/n][index%n], this->data[i][k], rhs[k][j]);
                product_matrix[index/n][index%n] = product_matrix[index/n][index%n] + (this->data[i][k] * rhs[k][j]);
            }
            index = index + 1;
        }
    }
    return product_matrix;
}

std::vector<double>& Matrix::operator[](int i)
{
    return this->data[i];
}

void MatLib::gtInitialize()
{
    // initialize stack with a single 4x4 identity matrix

    this->mat_stack.clear();
    this->mat_stack.push_back(Matrix(IDENTITY));
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
    this->mat_stack.push_back(this->mat_stack.back()*T);
}

void MatLib::gtScale(double x, double y, double z)
{
    // create scale matrix
    Matrix S = {{x,0,0,0}, {0,y,0,0}, {0,0,z,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*S);
}

void MatLib::gtRotateX(double theta)
{
    // create rotation matrix
    Matrix Rx = {{1,0,0,0}, {0,cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0}, {0,sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply Rx by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Rx);
}

void MatLib::gtRotateY(double theta)
{
    // create rotation matrix
    Matrix Ry = {{cos(theta*M_PI/180.0),0,sin(theta*M_PI/180.0),0}, {0,1,0,0}, {-sin(theta*M_PI/180.0),0,cos(theta*M_PI/180.0),0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Ry);
}

void MatLib::gtRotateZ(double theta)
{
    // create rotation matrix
    Matrix Rz = {{cos(theta*M_PI/180.0),-sin(theta*M_PI/180.0),0,0}, {sin(theta*M_PI/180.0),cos(theta*M_PI/180.0),0,0}, {0,0,1,0}, {0,0,0,1}};

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Rz);
}
