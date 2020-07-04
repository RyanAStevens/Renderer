/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.cpp
*/

// Drawing Routines, like  OpenGL
#include <drawlib.h>

ProjectionSetter::ProjectionSetter()
{
    this->mode = "NULL";
}

void ProjectionSetter::setOrtho(double left, double right, double bottom, double top, double near, double far)
{
        this->mode = "ORTHO";
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
        this->near = near;
        this->far = far;
}

void ProjectionSetter::setPerspect(double fov, double near, double far)
{
        this->mode = "PERSPECT";
        this->fov = fov;
        this->near = near;
        this->far = far;
}

DrawLib::DrawLib(MatLib* matrix_lib_p)
{
   this->matrix_lib_p = matrix_lib_p; 
}

void DrawLib::gtOrtho(double left, double right, double bottom, double top, double near, double far)
{
    this->projMode.setOrtho(left, right, bottom, top, near, far);
}

void DrawLib::gtPerspective(double fov, double near, double far)
{
    this->projMode.setPerspect(fov, near, far);
}    

void DrawLib::gtBeginShape()
{
    //initialize point array
    this->vertices.clear();
}

void DrawLib::gtEndShape()
{
    Vertex vert1, vert2;
    //draw the shape
    for(int i = 0; i <= this->vertices.size(); i += 2)
    {
        //perform transformation
        vert1 = this->vertices[i];
        vert2 = this->vertices[i+1];
        vert1 = matrix_lib_p->matrix_mult(matrix_lib_p->mat_stack.back(), vert1);
        vert2 = matrix_lib_p->matrix_mult(matrix_lib_p->mat_stack.back(), vert2);
        
        //perform view projection
        if(0 == this->projMode.mode.compare("ORTHO"))
        {
        /*
            vert1[0] = (vert1[0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert1[1] = (vert1[1] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert1[2] = 0;
            vert2[0] = (vert2[0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert2[1] = (vert2[1] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert2[2] = 0;
        */

            vert1[0][0] = (vert1[0][0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert1[1][0] = (vert1[1][0] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert1[2][0] = 0;
            vert2[0][0] = (vert2[0][0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert2[1][0] = (vert2[1][0] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert2[2][0] = 0;
        }
        else
        { // mode is perspective
            k = tan(this->projMode.fov*M_PI/180/2.0);
            xP1 = vert1[0][0] / abs(vert1[2][0]);
            yP1 = vert1[1][0] / abs(vert1[2][0]);
            vert1[0][0] = (xP1 + k)*(width/(2*k));
            vert1[1][0] = (yP1 + k)*(height/(2*k));
            xP2 = vert2[0][0] / abs(vert2[2][0]);
            yP2 = vert2[1][0] / abs(vert2[2][0]);
            vert2[0][0] = (xP2 + k)*(width/(2*k));
            vert2[1][0] = (yP2 + k)*(height/(2*k));
        }
        //draw line
        line(vert1[0][0], height - vert1[1][0], vert2[0][0], height - vert2[1][0]);
        }
}

void DrawLib::gtVertex(double x_in, double y_in, double z_in)
{
    std::vector<double> x(4, 0.0);
    x.front() = x_in;
    std::vector<double> y(4, 0.0);
    y.front() = y_in;
    std::vector<double> z(4, 0.0);
    z.front() = z_in;
    std::vector<double> h(4, 0.0);
    h.front() = 1.0;
    
    Vertex v;
    
    v.push_back(x);
    v.push_back(y);
    v.push_back(z);
    v.push_back(h);
    
    vertices.push_back(v);
}
