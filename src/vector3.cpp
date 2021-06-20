/*
A 3D vector class that stores an x y and z component. It should
store these components in a length-3 array so that an indexing
operator can be well supported. You should also include operations 
for vector addition, vector subtraction, dot product, cross product,
scalar multiplication, and scalar division.
*/
#include <vector3.h>
#include <iostream>
#include <cmath>

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
    set_i(i);
    set_j(j);
    set_k(k);
}

void Vector3::operator=(const Vector3& rhs)
{   
    set_i(rhs.get_i());
    set_j(rhs.get_j());
    set_k(rhs.get_k());
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

void Vector3::print()
{
    printf("Vector3: <%f,%f,%f>\n", components[0], components[1], components[2]);
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

double Vector3::mag()
{
    return std::sqrt(std::pow(this->components[0], 2.0) + std::pow(this->components[1], 2.0) + std::pow(this->components[2], 2.0));
}

double Vector3::get_i() const
{
    return components[0];
}

void Vector3::set_i(const double i)
{
    components[0] = i;
}

double Vector3::get_j() const
{
    return components[1];
}

void Vector3::set_j(const double j)
{
    components[1] = j;
}

double Vector3::get_k() const
{
    return components[2];
}

void Vector3::set_k(const double k)
{
    components[2] = k;
}
