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
	void circle();
	void square();
	void cube();
	void face();
	void faces();
	void persp_initials();
	void face_test();
	void ortho_test();
	void ortho_test_scale();
	void ortho_test_rotate();
	void ortho_cube();
	void ortho_cube2();
	void persp_cube();
	void persp_multi_cubes();
};

#endif //DRAWLIB_H_ 
