#include <vector3h.h>

class Transform_Matrix{
public:
    Transform_Matrix();
    Transform_Matrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~Transform_Matrix();
    Transform_Matrix operator*(const Transform_Matrix& rhs);
    Vector3H  row[4];
};

