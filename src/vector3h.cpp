/*
A homogeneous 3D vector class that stores an x y and z component. It should
*/
#include <vector3h.h>
#include <iostream>

Vector3H::Vector3H()
{
//	std::cout << "Hello from default Vector3H constructor\n";	
    components[0] = 0.0;
    components[1] = 0.0;
    components[2] = 0.0;
    components[3] = 0.0;
}

Vector3H::~Vector3H()
{
//	std::cout << "Hello from Vector3H destructor\n";	
}

Vector3H::Vector3H(double i, double j, double k, double l)
{
    components[0] = i;
    components[1] = j;
    components[2] = k;
    components[3] = l;
}

double& Vector3H::operator[](int req)
{   
    return components[req];
}

Vector3H Vector3H::operator+(const Vector3H& rhs)
{   
    return Vector3H(components[0] + rhs.components[0], 
                   components[1] + rhs.components[1], 
                   components[2] + rhs.components[2], 
                   components[3] + rhs.components[3]);
}

Vector3H Vector3H::operator-(const Vector3H& rhs)
{   
    return Vector3H(components[0] - rhs.components[0], 
                   components[1] - rhs.components[1], 
                   components[2] - rhs.components[2],
                   components[3] - rhs.components[3]);
}

//scalar multiplication
Vector3H Vector3H::operator*(const double scalar)
{   
    return Vector3H(components[0] * scalar, 
                   components[1] * scalar, 
                   components[2] * scalar,
                   components[3] * scalar);
}

//scalar division 
Vector3H Vector3H::operator/(const double scalar)
{   
    return Vector3H(components[0] / scalar, 
                   components[1] / scalar, 
                   components[2] / scalar,
                   components[3] / scalar);
}

//// This may not make sense in 4D, but I'm leaving it for now
// u * v = u0*v0 + u1*v1 + u2*v2 + u3*v3
double Vector3H::dot(const Vector3H& rhs)
{
    return components[0]*rhs.components[0] + components[1]*rhs.components[1] + components[2]*rhs.components[2] + components[3]*rhs.components[3];
}
/*
//// This may not make sense in 4D, but I'm leaving it for now
// u x v = (u1*v2 - u2*v1)i - (u0*v2 - u2*v0)j + (u0*v1 - u1*v0)k
Vector3H Vector3H::cross(const Vector3H& rhs)
{
    return Vector3H((components[1]*rhs.components[2] - components[2]*rhs.components[1]),
                   (components[0]*rhs.components[2] - components[2]*rhs.components[0]) * -1,
                   (components[0]*rhs.components[1] - components[1]*rhs.components[0]));
}
*/
