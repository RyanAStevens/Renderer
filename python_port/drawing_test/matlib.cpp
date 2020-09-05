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
            data[0][0] = 1.0;
            data[1][1] = 1.0;
            data[2][2] = 1.0;
            data[3][3] = 1.0;
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
    std::vector<double> x = {x_in};
    std::vector<double> y = {y_in};
    std::vector<double> z = {z_in};
    std::vector<double> h = {1.0};
    
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
    std::vector<std::vector<double>>::iterator it_i;
    std::vector<double>::iterator it_j;
    for(it_i = this->data.begin(); it_i != this->data.end(); ++it_i)
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
    //A(l x m) * B(m x n) = C(l x n)
    int l = this->data.size();
    int n = rhs.data.front().size();
    int m = rhs.data.size();

    //initialize the return matrix
    Matrix product_matrix(l, n);
    
    //check for proper input
    if(this->data.front().size() != rhs.data.size())
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
                product_matrix[index/n][index%n] = product_matrix[index/n][index%n] + (this->data[i][k] * rhs[k][j]);
            }
            index = index + 1;
        }
    }
   // printf("goodbye from Matrix::operator*\n");
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
    Matrix T(IDENTITY);
    T[0][3] = x;
    T[1][3] = y;
    T[2][3] = z;
    
    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*T);
}

void MatLib::gtScale(double x, double y, double z)
{
    // create scale matrix
    Matrix S(IDENTITY);
    S[0][0] = x;
    S[1][1] = y;
    S[2][2] = z;

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*S);
}

void MatLib::gtRotateX(double theta)
{
    // create rotation matrix
    Matrix Rx(IDENTITY);
    Rx[1][1] = cos(theta*M_PI/180.0);
    Rx[1][2] = -sin(theta*M_PI/180.0);
    Rx[2][1] = sin(theta*M_PI/180.0);
    Rx[2][2] = cos(theta*M_PI/180.0);

    //multiply Rx by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Rx);
}

void MatLib::gtRotateY(double theta)
{
    // create rotation matrix
    Matrix Ry(IDENTITY);
    Ry[0][0] = cos(theta*M_PI/180.0);
    Ry[0][2] = sin(theta*M_PI/180.0);
    Ry[2][0] = -sin(theta*M_PI/180.0);
    Ry[2][2] = cos(theta*M_PI/180.0);

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Ry);
}

void MatLib::gtRotateZ(double theta)
{
    // create rotation matrix
    Matrix Rz(IDENTITY);
    Rz[0][0] = cos(theta*M_PI/180.0);
    Rz[0][1] = -sin(theta*M_PI/180.0);
    Rz[1][0] = sin(theta*M_PI/180.0);
    Rz[1][1] = cos(theta*M_PI/180.0);

    //multiply by CTM
    this->mat_stack.push_back(this->mat_stack.back()*Rz);
}
