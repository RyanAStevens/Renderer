/*
A homogeneour 3D vector.
*/

class Vector3H {
public:
    Vector3H();
    Vector3H(double i, double j, double k, double l);
    ~Vector3H();
    float components[4];
    Vector3H operator+(const Vector3H& rhs);
    Vector3H operator-(const Vector3H& rhs);
    Vector3H operator*(const double scalar);
    Vector3H operator/(const double scalar);
    double dot(const Vector3H& rhs);
    Vector3H cross(const Vector3H& rhs);
};

