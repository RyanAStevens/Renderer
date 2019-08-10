/*
A 2D vector class that stores an x and y component. It should
store these components in a length-2 array so that an indexing
operator can be well supported. You should also include operations 
for vector addition, vector subtraction, dot product, cross product,
scalar multiplication, and scalar division.
*/
#include "../include/vector2.h"

Vector2::Vector2(double i, double j)
{
    this->components[0] = i;
    this->components[1] = j;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{   
    return Vector2(this->components[0] + rhs.components[0], this->components[1] + rhs.components[1]);
}   
