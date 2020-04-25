#ifndef DRAWLIB_H_ 
#define DRAWLIB_H_ 

/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.h
*/

#include <string>

// Drawing Routines, like  OpenGL

//Class for vertex object
class Vertex
{
public:
    float x, y, z;
    const int h = 1;
};

//Class to keep track of projection settings
class ProjectionSetter
{
public:
    ProjectionSetter();
    std::string mode = "NULL";
    float left, right, bottom, top, near, far, fov;
    void setOrtho(float left, float right, float bottom, float top, float near, float far);
    void setPerspect(float fov, float near, float far);
};

class DrawLib
{
public:
        DrawLib();
        ProjectionSetter projMode;
        std::vector<Vertex> vertices;
        matrix_stack* mat_stack_p;
        void gtOrtho(float left, float right, float bottom, float top, float near, float far);
        void gtPerspective(float fov, float near, float far);
        void gtBeginShape();
        void gtEndShape();
        void gtVertex(float x, float y, float z);
};

#endif //DRAWLIB_H_ 
