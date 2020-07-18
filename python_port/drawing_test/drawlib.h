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
#include <matlib.h>
#include <graphics_lib.h>
//#include <vector3.h>

// Drawing Routines, like  OpenGL

typedef matrix Vertex;

//Class to keep track of projection settings
class ProjectionSetter
{
public:
    ProjectionSetter();
    std::string mode = "NULL";
    double left, right, bottom, top, near, far, fov;
    void setOrtho(double left, double right, double bottom, double top, double near, double far);
    void setPerspect(double fov, double near, double far);
};

class DrawLib
{
public:
        DrawLib(MatLib* matrix_lib_p, GraphicsLib* graphics_lib_p, double width, double height);
        ProjectionSetter projMode;
        std::vector<Vertex> vertices;
        MatLib* matrix_lib_p;
        GraphicsLib* graphics_lib_p;
        double width;
        double height;
        matrix_stack* mat_stack_p;
        void gtOrtho(double left, double right, double bottom, double top, double near, double far);
        void gtPerspective(double fov, double near, double far);
        void gtBeginShape();
        void gtEndShape();
        void gtVertex(double x, double y, double z);
};

#endif //DRAWLIB_H_ 
