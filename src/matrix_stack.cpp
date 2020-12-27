/*
Transformation matrix stack
*/
#include <iostream>
#include <math.h>
#include <matrix_stack.h>
#include <stack_trace.h>

#define CON_RAD 0.01745329251  

MatrixStack::MatrixStack()
{
    printf("hello from MatrixStack default constructor\n");
        std::cout << "_stack.size() = " << _stack.size() << std::endl;
        std::cout << "_stack.empty() = " << _stack.empty() << std::endl;
    _stack.push(Matrix());
        std::cout << "_stack.size() = " << _stack.size() << std::endl;
        std::cout << "_stack.empty() = " << _stack.empty() << std::endl;
    printf("hello from MatrixStack default constructor\n");
}

MatrixStack::~MatrixStack()
{
}

//stack will only have the identity matrix
void MatrixStack::initialize()
{   
    printf("hello from MatrixStack::initialize\n");
    //identity matrix is added on construction
    //,so pop everything down to that
    while(_stack.size() > 1)
    {
        std::cout << "_stack.size() = " << _stack.size() << std::endl;
        std::cout << "_stack.empty() = " << _stack.empty() << std::endl;
        _stack.pop();
    }
    printf("goodbyefrom MatrixStack::initialize\n");
}

void MatrixStack::print_ctm()
{
    Matrix tm = _stack.top();
    std::cout << "-------------\n";
    int i = 0;
    int j = 0;
    for(; i < 4; i++)
    {
        for(j=0; j < 4; j++)
        {
            std::cout << (*tm.data)[i].components[j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-------------\n";
}

Matrix& MatrixStack::get_ctm()
{
    return _stack.top();
}

void MatrixStack::translate(float x, float y, float z)
{
   Matrix tm = Matrix();
   (*tm.data)[0].components[3] = x;
   (*tm.data)[1].components[3] = y;
   (*tm.data)[2].components[3] = z;

   Matrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::scale(float x, float y, float z)
{
   Matrix tm = Matrix();
   (*tm.data)[0].components[0] = x;
   (*tm.data)[1].components[1] = y;
   (*tm.data)[2].components[2] = z;

   Matrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::rotate_x(float theta)
{
   float thetaRad = theta * CON_RAD;
   Matrix tm = Matrix();
   (*tm.data)[1].components[1] = cos(thetaRad);
   (*tm.data)[1].components[2] = -1*sin(thetaRad);
   (*tm.data)[2].components[1] = sin(thetaRad);
   (*tm.data)[2].components[2] = cos(thetaRad);

   Matrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::rotate_y(float theta)
{
   printf("hello from MatrixStack::rotate_y\n");
   float thetaRad = theta * CON_RAD;
   printf("MatrixStack::rotate_y 1\n");
   Matrix tm = Matrix();
   printf("MatrixStack::rotate_y 2\n");

   (*tm.data)[0].components[0] = cos(thetaRad);
   printf("MatrixStack::rotate_y 3\n");
   (*tm.data)[0].components[2] = sin(thetaRad);
   printf("MatrixStack::rotate_y 4\n");
   (*tm.data)[2].components[0] = -1*sin(thetaRad);
   printf("MatrixStack::rotate_y 5\n");
   (*tm.data)[2].components[2] = cos(thetaRad);
   printf("MatrixStack::rotate_y 6\n");

   Matrix result = _stack.top()*tm;
   printf("MatrixStack::rotate_y 7\n");
   _stack.push(result);
}

void MatrixStack::rotate_z(float theta)
{
   float thetaRad = theta * CON_RAD;
   Matrix tm = Matrix();
   (*tm.data)[0].components[0] = cos(thetaRad);
   (*tm.data)[0].components[1] = -1*sin(thetaRad);
   (*tm.data)[1].components[0] = sin(thetaRad);
   (*tm.data)[1].components[1] = cos(thetaRad);

   Matrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::push_matrix()
{
    _stack.push(_stack.top());
}

int32_t MatrixStack::pop_matrix()
{
    if(_stack.size() > 0)
    {
        _stack.pop();
        return 0;
    }
    else
    {
        std::cout << "Cannot pop matrix stack. Stack is empty\n";
        return -1;
    }
}
