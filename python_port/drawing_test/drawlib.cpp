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
    Matrix transform(IDENTITY);
    Matrix vert1(0,0,0);
    Matrix vert2(0,0,0);
    //draw the shape
    for(int i = 0; i < this->vertices.size(); i += 2)
    {
        //perform transformation
        vert1 = this->vertices[i];
        vert2 = this->vertices[i+1];
        this->matrix_lib_p->gtInitialize();
        transform = this->matrix_lib_p->mat_stack.back();
        vert1 = transform*vert1;
        vert2 = transform*vert2;
        
        //perform view projection
        if(0 == this->projMode.mode.compare("ORTHO"))
        {
            vert1[0][0] = (vert1[0][0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert1[1][0] = (vert1[1][0] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert1[2][0] = 0;
            vert2[0][0] = (vert2[0][0] - this->projMode.left)*(width/(this->projMode.right - this->projMode.left));
            vert2[1][0] = (vert2[1][0] - this->projMode.bottom)*(width/(this->projMode.top - this->projMode.bottom));
            vert2[2][0] = 0;
        }
        else
        { // mode is perspective
            if(0.0 != this->projMode.fov)
            {
                double k = tan(this->projMode.fov*M_PI/90.0);
                if(0.0 != vert1[2][0])
                {
                    double xP1 = vert1[0][0] / abs(vert1[2][0]);
                    double yP1 = vert1[1][0] / abs(vert1[2][0]);
                    vert1[0][0] = (xP1 + k)*(width/(2*k));
                    vert1[1][0] = (yP1 + k)*(height/(2*k));
                }
                
                if(0.0 != vert2[2][0])
                {
                    double xP2 = vert2[0][0] / abs(vert2[2][0]);
                    double yP2 = vert2[1][0] / abs(vert2[2][0]);
                    vert2[0][0] = (xP2 + k)*(width/(2*k));
                    vert2[1][0] = (yP2 + k)*(height/(2*k));
                }
                
            }
        }
        //draw line
        this->graphics_lib_p->draw_line(vert1[0][0], height - vert1[1][0], vert2[0][0], height - vert2[1][0]);
    }
}

void DrawLib::gtVertex(double x_in, double y_in, double z_in)
{
    Matrix v(x_in, y_in, z_in);
    vertices.push_back(v);
}

void DrawLib::create_window(const char title[], uint32_t width, uint32_t height, p_mode_t draw_mode)
{
    this->graphics_lib_p->create_window(title, width, height, draw_mode);
}

void DrawLib::listen_window(Application* app)
{
    this->graphics_lib_p->window->listen(app);
}

uint32_t DrawLib::window_open()
{
    return this->graphics_lib_p->window->open();
}

void DrawLib::update_window()
{
    this->graphics_lib_p->window->update();
}
