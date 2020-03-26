#include <vector3h.h>

#define NUM_ROWS 4
#define NUM_COMPS 4

class TransformMatrix{
public:
    TransformMatrix();
    TransformMatrix(Vector3H, Vector3H, Vector3H, Vector3H);
    ~TransformMatrix();
    TransformMatrix operator*(const TransformMatrix& rhs);
    TransformMatrix operator=(const TransformMatrix& rhs);
    Vector3H  row[4];
};

