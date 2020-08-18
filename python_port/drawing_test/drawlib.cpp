/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.cpp
*/

// Drawing Routines, like  OpenGL
#include <drawlib.h>

Vertex::Vertex(): Matrix() {};

Vertex::Vertex(double x_in, double y_in, double z_in)
{
    std::vector<double> x(x_in);
    std::vector<double> y(y_in);
    std::vector<double> z(z_in);
    std::vector<double> h(1.0);
    
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(h);
    
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
   data0
}

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

DrawLib::DrawLib(MatLib* matrix_lib_p, GraphicsLib* graphics_lib_p, double width, double height)
{
   this->graphics_lib_p = graphics_lib_p;
   this->matrix_lib_p = matrix_lib_p;
   this->width = width;
   this->height = height;
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
    printf("hello from gtEndShape()\n");
    Vertex vert1;
    Vertex vert2;
    //draw the shape
    for(int i = 0; i <= this->vertices.size(); i += 2)
    {
        printf("gtEndShape: 1\n");
        //perform transformation
        vert1 = this->vertices[i];
        vert2 = this->vertices[i+1];
        printf("gtEndShape: 2\n");
        printf("matrix_lib_p = %u\n", this->matrix_lib_p);
        printf("matrix_lib_p->mat_stack = %u\n", this->matrix_lib_p->mat_stack);
        this->matrix_lib_p->gtInitialize();
        printf("gtEndShape: 3\n");
        vert1 = this->matrix_lib_p->matrix_mult(this->matrix_lib_p->mat_stack.back(), vert1);
        printf("gtEndShape: 4\n");
        vert2 = this->matrix_lib_p->matrix_mult(this->matrix_lib_p->mat_stack.back(), vert2);
        printf("drawlib:gtEndShape vert1(%f, %f, %f) vert2(%f, %f, %f)\n", vert1[0][0], vert1[0][0], vert1[1][0], vert1[2][0], vert2[0][0], vert2[1][0], vert2[2][0]);
        
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
            printf("drawlib:ortho vert1(%f, %f, %f) vert2(%f, %f, %f)\n", vert1[0][0], vert1[0][0], vert1[1][0], vert1[2][0], vert2[0][0], vert2[1][0], vert2[2][0]);
        }
        else
        { // mode is perspective
        printf("gtEndShape: 5\n");
            double k = tan(this->projMode.fov*M_PI/180/2.0);
            double xP1 = vert1[0][0] / abs(vert1[2][0]);
            double yP1 = vert1[1][0] / abs(vert1[2][0]);
            vert1[0][0] = (xP1 + k)*(width/(2*k));
            vert1[1][0] = (yP1 + k)*(height/(2*k));
            double xP2 = vert2[0][0] / abs(vert2[2][0]);
            double yP2 = vert2[1][0] / abs(vert2[2][0]);
            vert2[0][0] = (xP2 + k)*(width/(2*k));
            vert2[1][0] = (yP2 + k)*(height/(2*k));
            printf("drawlib:perspective vert1(%f, %f, %f) vert2(%f, %f, %f)\n", vert1[0][0], vert1[0][0], vert1[1][0], vert1[2][0], vert2[0][0], vert2[1][0], vert2[2][0]);
        }
        printf("gtEndShape: 6\n");
        //draw line
        printf("this->graphics_lib_p->draw_line(%f, %f, %f, %f)\n",vert1[0][0], height - vert1[1][0], vert2[0][0], height - vert2[1][0]);
        this->graphics_lib_p->draw_line(vert1[0][0], height - vert1[1][0], vert2[0][0], height - vert2[1][0]);
    }
}

void DrawLib::gtVertex(double x_in, double y_in, double z_in)
{
    Vertex v(x_in, y_in, z_in);
    vertices.push_back(v);
}
