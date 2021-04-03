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
    _stack.push(TransformMatrix());
}

MatrixStack::~MatrixStack()
{
}

//stack will only have the identity matrix
void MatrixStack::initialize()
{   
    //identity matrix is added on construction
    //,so pop everything down to that
    while(_stack.size() > 1)
    {
        _stack.pop();
    }
}

void MatrixStack::print_ctm()
{
    TransformMatrix tm = _stack.top();
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

TransformMatrix& MatrixStack::get_ctm()
{
    return _stack.top();
}

void MatrixStack::translate(float x, float y, float z)
{
   TransformMatrix tm;
   (*tm.data)[0].components[3] = x;
   (*tm.data)[1].components[3] = y;
   (*tm.data)[2].components[3] = z;

   _stack.top() = _stack.top()*tm;
}

void MatrixStack::scale(float x, float y, float z)
{
   TransformMatrix tm;
   (*tm.data)[0].components[0] = x;
   (*tm.data)[1].components[1] = y;
   (*tm.data)[2].components[2] = z;

   _stack.top() = _stack.top()*tm;
}

void MatrixStack::rotate_x(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm;
   (*tm.data)[1].components[1] = cos(thetaRad);
   (*tm.data)[1].components[2] = -1*sin(thetaRad);
   (*tm.data)[2].components[1] = sin(thetaRad);
   (*tm.data)[2].components[2] = cos(thetaRad);

   _stack.top() = _stack.top()*tm;
}

void MatrixStack::rotate_y(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm;
   (*tm.data)[0].components[0] = cos(thetaRad);
   (*tm.data)[0].components[2] = sin(thetaRad);
   (*tm.data)[2].components[0] = -1*sin(thetaRad);
   (*tm.data)[2].components[2] = cos(thetaRad);

   _stack.top() = _stack.top()*tm;
}

void MatrixStack::rotate_z(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm;
   (*tm.data)[0].components[0] = cos(thetaRad);
   (*tm.data)[0].components[1] = -1*sin(thetaRad);
   (*tm.data)[1].components[0] = sin(thetaRad);
   (*tm.data)[1].components[1] = cos(thetaRad);

   _stack.top() = _stack.top()*tm;
}

int32_t MatrixStack::size()
{
    return _stack.size();
}

void MatrixStack::push_matrix()
{
    _stack.push(_stack.top());
    //_stack.push(TransformMatrix(_stack.top()));
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
