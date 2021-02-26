#ifndef PROJECTION_H_ 
#define PROJECTION_H_

#include <vector3.h>
#include <string>
#include <stdint.h>

enum p_mode_t 
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Projection
{
public:
    Projection();
    Projection(uint32_t height, uint32_t width);
    double left, right, bottom, top, near, far;
    double fov;
    uint32_t height, width;
    p_mode_t mode;
    Matrix *matrix;
};

class Orthographic : public Projection
{
public:
    Orthographic();
    Orthographic(uint32_t height, uint32_t width);
    void project_vertex(Vector3);
};

class Perspective : public Projection
{
public:
    Perspective();
    Perspective(uint32_t height, uint32_t width);
    void project_vertex(Vector3);
};

#endif //PROJECTION_H_
