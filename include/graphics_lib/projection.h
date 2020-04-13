#include <vector3.h>
#include <string>

class Projection
{
    double left, right, bottom, top, near, far;
    double fov, near, far;
};

class Orthographic : public Projection
{
    void project_vertex(Vector3);
    std::string type = "Orthographic";
};

class Perspective : public Projection
{
    void project_vertex(Vector3);
    std::string type = "Perspective";
};
