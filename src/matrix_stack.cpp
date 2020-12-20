/*
Transformation matrix stack
*/
#include <iostream>
#include <math.h>
#include <matrix_stack.h>

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
    for(; i < NUM_ROWS; i++)
    {
        for(j=0; j < NUM_COMPS; j++)
        {
            std::cout << tm.row[i].components[j] << ' ';
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
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[3] = x;
   tm.row[1].components[3] = y;
   tm.row[2].components[3] = z;

   TransformMatrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::scale(float x, float y, float z)
{
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = x;
   tm.row[1].components[1] = y;
   tm.row[2].components[2] = z;

   TransformMatrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::rotate_x(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm = TransformMatrix();
   tm.row[1].components[1] = cos(thetaRad);
   tm.row[1].components[2] = -1*sin(thetaRad);
   tm.row[2].components[1] = sin(thetaRad);
   tm.row[2].components[2] = cos(thetaRad);

   TransformMatrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::rotate_y(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = cos(thetaRad);
   tm.row[0].components[2] = sin(thetaRad);
   tm.row[2].components[0] = -1*sin(thetaRad);
   tm.row[2].components[2] = cos(thetaRad);

   TransformMatrix result = _stack.top()*tm;
   _stack.push(result);
}

void MatrixStack::rotate_z(float theta)
{
   float thetaRad = theta * CON_RAD;
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = cos(thetaRad);
   tm.row[0].components[1] = -1*sin(thetaRad);
   tm.row[1].components[0] = sin(thetaRad);
   tm.row[1].components[1] = cos(thetaRad);

   TransformMatrix result = _stack.top()*tm;
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
