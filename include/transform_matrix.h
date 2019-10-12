#include <vector3h.h>

class Transform_Matrix{
public:
    Transform_Matrix();
    ~Transform_Matrix();
    Transform_Matrix operator*(const Transform_Matrix& rhs);
private:
    Vector3H  row[4];
};

