/*
Transformation matrix stack
*/
#include <iostream>
#include <math.h>
#include <matrix_stack.h>

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

   TransformMatrix result = tm*_stack.top();
   _stack.push(result);
}

void MatrixStack::scale(float x, float y, float z)
{
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = x;
   tm.row[1].components[1] = y;
   tm.row[2].components[2] = z;

   TransformMatrix result = tm*_stack.top();
   _stack.push(result);
}

void MatrixStack::rotateX(float theta)
{
   TransformMatrix tm = TransformMatrix();
   tm.row[1].components[1] = cos(theta);
   tm.row[1].components[2] = -1*sin(theta);;
   tm.row[2].components[1] = sin(theta);
   tm.row[2].components[2] = cos(theta);

   TransformMatrix result = tm*_stack.top();
   _stack.push(result);
}

void MatrixStack::rotateY(float theta)
{
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = cos(theta);
   tm.row[0].components[2] = sin(theta);;
   tm.row[2].components[0] = -1*sin(theta);
   tm.row[2].components[2] = cos(theta);

   TransformMatrix result = tm*_stack.top();
   _stack.push(result);
}

void MatrixStack::rotateZ(float theta)
{
   TransformMatrix tm = TransformMatrix();
   tm.row[0].components[0] = cos(theta);
   tm.row[0].components[1] = -1*sin(theta);;
   tm.row[1].components[0] = sin(theta);
   tm.row[1].components[1] = cos(theta);

   TransformMatrix result = tm*_stack.top();
   _stack.push(result);
}

void MatrixStack::pushMatrix()
{
    _stack.push(_stack.top());
}

void MatrixStack::popMatrix()
{
    _stack.pop();
}
