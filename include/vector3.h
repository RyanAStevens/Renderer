/*
A 3D vector class analogous to vector2.
*/

class Vector3 {
public:
    Vector3();
    Vector3(double i, double j, double k);
    ~Vector3();
    float components[3];
    void operator=(const Vector3& rhs);
    Vector3 operator+(const Vector3& rhs);
    Vector3 operator-(const Vector3& rhs);
    Vector3 operator*(const double scalar);
    Vector3 operator/(const double scalar);
    double dot(const Vector3& rhs);
    Vector3 cross(const Vector3& rhs);
    double mag();
    void set_i(const double i);
    double get_i() const;
    void set_j(const double i);
    double get_j() const;
    void set_k(const double i);
    double get_k() const;
};

