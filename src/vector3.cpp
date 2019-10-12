/*
A 3D vector class that stores an x y and z component. It should
store these components in a length-3 array so that an indexing
operator can be well supported. You should also include operations 
for vector addition, vector subtraction, dot product, cross product,
scalar multiplication, and scalar division.
*/
#include "../include/vector3.h"
#include <iostream>

Vector3::Vector3()
{
//	std::cout << "Hello from default Vector3 constructor\n";	
}

Vector3::~Vector3()
{
//	std::cout << "Hello from Vector3 destructor\n";	
}

Vector3::Vector3(double i, double j, double k)
{
    this->components[0] = i;
    this->components[1] = j;
    this->components[2] = k;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{   
    return Vector3(this->components[0] + rhs.components[0], 
                   this->components[1] + rhs.components[1], 
                   this->components[2] + rhs.components[2]);
}

Vector3 Vector3::operator-(const Vector3& rhs)
{   
    return Vector3(this->components[0] - rhs.components[0], 
                   this->components[1] - rhs.components[1], 
                   this->components[2] - rhs.components[2]);
}

//scalar multiplication
Vector3 Vector3::operator*(const double scalar)
{   
    return Vector3(this->components[0] * scalar, 
                   this->components[1] * scalar, 
                   this->components[2] * scalar);
}

//scalar division 
Vector3 Vector3::operator/(const double scalar)
{   
    return Vector3(this->components[0] / scalar, 
                   this->components[1] / scalar, 
                   this->components[2] / scalar);
}

// u * v = u1*v1 + u2*v2
double Vector3::dot(const Vector3& rhs)
{
    return this->components[0]*rhs.components[0] + this->components[1]*rhs.components[1] + this->components[2]*rhs.components[2];
}

// u x v = (u1*v2 - u2*v1)i - (u0*v2 - u2*v0)j + (u0*v1 - u1*v0)k
Vector3 Vector3::cross(const Vector3& rhs)
{
    return Vector3((this->components[1]*rhs.components[2] - this->components[2]*rhs.components[1]),
                   (this->components[0]*rhs.components[2] - this->components[2]*rhs.components[0]) * -1,
                   (this->components[0]*rhs.components[1] - this->components[1]*rhs.components[0]));
}
