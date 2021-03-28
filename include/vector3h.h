/*
A homogeneous 3D vector.
*/

#ifndef VECTOR3H_H_
#define VECTOR3H_H_

class Vector3H {
public:
    Vector3H();
    Vector3H(double i, double j, double k, double l);
    ~Vector3H();
   
    double& operator[](int req);
    Vector3H operator+(const Vector3H& rhs);
    Vector3H operator-(const Vector3H& rhs);
    Vector3H operator*(const double scalar);
    Vector3H operator/(const double scalar);
    double dot(const Vector3H& rhs);
    Vector3H cross(const Vector3H& rhs);
    
    double components[4];
};

#endif //VECTOR3H_H_

