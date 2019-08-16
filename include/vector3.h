/*
A 3D vector class analogous to vector2.
*/

class Vector3 {
public:
    Vector3();
    Vector3(double i, double j, double k);
    ~Vector3();
    float components[2];
    Vector3 operator+(const Vector3& rhs);
    Vector3 operator-(const Vector3& rhs);
    Vector3 operator*(const double scalar);
    Vector3 operator/(const double scalar);
    double dot(const Vector3& rhs);
    Vector3 cross(const Vector3& rhs);
};

