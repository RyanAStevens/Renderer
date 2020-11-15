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
#include <projection.h>

//#include <vector3.h>

// Drawing Routines, like  OpenGL

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

class GraphicsLib;
class Application;

class DrawLib
{
public:
        DrawLib(MatLib* matrix_lib_p, GraphicsLib* graphics_lib_p, double width, double height);
        ProjectionSetter projMode;
        std::vector<Matrix> vertices;
        MatLib* matrix_lib_p;
        GraphicsLib* graphics_lib_p;
        matrix_stack* mat_stack_p;
        double width;
        double height;
        void gtOrtho(double left, double right, double bottom, double top, double near, double far);
        void gtPerspective(double fov, double near, double far);
        void gtBeginShape();
        void gtEndShape();
        void gtVertex(double x, double y, double z);
        void create_window(const char title[], uint32_t width, uint32_t height, p_mode_t draw_mode);
        void listen_window(Application* app);
        uint32_t window_open();
        void update_window();
};

#endif //DRAWLIB_H_ 
