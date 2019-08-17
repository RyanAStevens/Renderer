/*
A 2D vector class that stores an x and y component. It should
store these components in a length-2 array so that an indexing
operator can be well supported. You should also include operations 
for vector addition, vector subtraction, dot product, cross product,
scalar multiplication, and scalar division.
*/
#include "../include/vector2.h"
#include <iostream>

Vector2::Vector2()
{
//	std::cout << "Hello from default Vector2 constructor\n";	
}

Vector2::~Vector2()
{
//	std::cout << "Hello from Vector2 destructor\n";	
}

Vector2::Vector2(double i, double j)
{
    this->components[0] = i;
    this->components[1] = j;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{   
    return Vector2(this->components[0] + rhs.components[0], this->components[1] + rhs.components[1]);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{   
    return Vector2(this->components[0] - rhs.components[0], this->components[1] - rhs.components[1]);
}

//scalar multiplication
Vector2 Vector2::operator*(const double scalar)
{   
    return Vector2(this->components[0] * scalar, this->components[1] * scalar);
}

//scalar division 
Vector2 Vector2::operator/(const double scalar)
{   
    return Vector2(this->components[0] / scalar, this->components[1] / scalar);
}

// u * v = u1*v1 + u2*v2
double Vector2::dot(const Vector2& rhs)
{
    return this->components[0]*rhs.components[0] + this->components[1]*rhs.components[1];
}

// u x v = u1*v2 - u2*v1
double Vector2::cross(const Vector2& rhs)
{
    return this->components[0]*rhs.components[1] - this->components[1]*rhs.components[0];
}
