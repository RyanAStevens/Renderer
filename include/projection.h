#ifndef PROJECTION_H_ 
#define PROJECTION_H_

#include <vector3.h>
#include <transform_matrix.h>
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
    Projection(enum p_mode_t proj_mode, uint32_t height, uint32_t width);
    void set_projection(enum p_mode_t proj_mode);
    double left, right, bottom, top, near, far;
    double fov;
    uint32_t height, width;
    p_mode_t mode;
    TransformMatrix *matrix;
};

#endif //PROJECTION_H_
