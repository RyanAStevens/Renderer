/*
A 2D vector class that stores an x and y component. It should
store these components in a length-2 array so that an indexing
operator can be well supported. You should also include operations 
for vector addition, vector subtraction, dot product, cross product,
scalar multiplication, and scalar division.
*/

class Vector2 { 
public:
    Vector2();
    Vector2(double i, double j);
    ~Vector2();
    float components[2];
    Vector2 operator+(const Vector2& rhs);
    Vector2 operator-(const Vector2& rhs);
    Vector2 operator*(const double scalar);
    Vector2 operator/(const double scalar);
    double dot(const Vector2& rhs);
    double cross(const Vector2& rhs);
};
