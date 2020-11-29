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

// unit radius cirle
void DrawLib::circle()
{
    printf("hello from circle\n");
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
    gtBeginShape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        gtVertex (xold, yold, 0);
        gtVertex (x, y, 0);
        xold = x;
        yold = y;
    }

    gtEndShape();
    printf("goodbye from circle\n");
}

void DrawLib::square()
{
    printf("hello from square\n");
  gtBeginShape ();

  gtVertex (-50, -50, 0);
  gtVertex (-50, 50, 0);
  
  gtVertex (-50, 50, 0);
  gtVertex (50, 50, 0);

  gtVertex (50, 50, 0);
  gtVertex (50, -50, 0);

  gtVertex (50, -50, 0);
  gtVertex (-50, -50, 0);

  gtEndShape();
    printf("goodbye from square\n");
}

void DrawLib::cube()
{
    printf("hello from cube\n");
    gtBeginShape();
    
    // top square
    
    gtVertex (-1.0, -1.0,  1.0);
    gtVertex (-1.0,  1.0,  1.0);

    gtVertex (-1.0,  1.0,  1.0);
    gtVertex ( 1.0,  1.0,  1.0);

    gtVertex ( 1.0,  1.0,  1.0);
    gtVertex ( 1.0, -1.0,  1.0);

    gtVertex ( 1.0, -1.0,  1.0);
    gtVertex (-1.0, -1.0,  1.0);

    // bottom square
    
    gtVertex (-1.0, -1.0, -1.0);
    gtVertex (-1.0,  1.0, -1.0);
    
    gtVertex (-1.0,  1.0, -1.0);
    gtVertex ( 1.0,  1.0, -1.0);
    
    gtVertex ( 1.0,  1.0, -1.0);
    gtVertex ( 1.0, -1.0, -1.0);
    
    gtVertex ( 1.0, -1.0, -1.0);
    gtVertex (-1.0, -1.0, -1.0);
    
    // connect top to bottom
    
    gtVertex (-1.0, -1.0, -1.0);
    gtVertex (-1.0, -1.0,  1.0);
    
    gtVertex (-1.0,  1.0, -1.0);
    gtVertex (-1.0,  1.0,  1.0);
    
    gtVertex ( 1.0,  1.0, -1.0);
    gtVertex ( 1.0,  1.0,  1.0);
    
    gtVertex ( 1.0, -1.0, -1.0);
    gtVertex ( 1.0, -1.0,  1.0);
   
    gtEndShape();
    printf("goodbye from cube\n");
}

// draw a face by transforming circles;
void DrawLib::face()
{
    printf("hello from face\n");
    // head
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.5, 0);
    matrix_lib_p->gtScale (0.4, 0.4, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // right eye
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.7, 0.7, 0.0);
    matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // // left eye
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.3, 0.7, 0.0);
    matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // nose
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.5, 0.0);
    matrix_lib_p->gtScale (0.07, 0.07, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // mouth
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.25, 0.0);
    matrix_lib_p->gtScale (0.2, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from face\n");
}

// draw several faces
void DrawLib::faces()
{
    printf("hello from faces\n");
    matrix_lib_p->gtInitialize ();
    
    gtOrtho (0, 1, 0, 1, -1, 1);
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.75, 0.25, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.25, 0.25, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.75, 0.75, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.25, 0.75, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtRotateZ (30);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from faces\n");
} 

void DrawLib::persp_initials()
{
    printf("hello from persp_initials\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -4);
    matrix_lib_p->gtRotateZ(-45);
    matrix_lib_p->gtRotateX(-45);
    matrix_lib_p->gtRotateY(-45);

    gtBeginShape();

    //Draw R
    gtVertex(-1, 1, 0);
    gtVertex(0, 1, 0);

    gtVertex(-1, 1, 0);
    gtVertex(-1, 0.5, 0);

    gtVertex(0, 1, 0);
    gtVertex(0, 0.5, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(-1, 0, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(0, 0.5, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(0, 0, 0);

    //draw S
    gtVertex(0.2, 0.5, 0);
    gtVertex(1, 0.5, 0);

    gtVertex(0.2, 0.5, 0);
    gtVertex(0.2, 0, 0);

    gtVertex(0.2, 0, 0);
    gtVertex(1, 0, 0);

    gtVertex(1, 0, 0);
    gtVertex(1, -1, 0);

    gtVertex(1, -1, 0);
    gtVertex(0.2, -1, 0);

    gtEndShape();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_initials\n");
}

void DrawLib::face_test()
{
    printf("hello from face_test\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (0, 1, 0, 1, -1, 1);
    face();
    printf("goodbye from face_test\n");
}

void DrawLib::ortho_test()
{
    printf("hello from ortho_test\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test\n");
}

void DrawLib::ortho_test_scale()
{
    printf("hello from ortho_test_scale\n");
    matrix_lib_p->gtInitialize();
    matrix_lib_p->gtScale(1,0.5,1);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_scale\n");
}

void DrawLib::ortho_test_rotate()
{
    printf("hello from ortho_test_rotate\n");
    matrix_lib_p->gtInitialize();
    matrix_lib_p->gtRotateZ(20);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_rotate\n");
}

void DrawLib::ortho_cube()
{
    printf("hello from ortho_cube\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtRotateY(17);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube\n");
}

void DrawLib::ortho_cube2()
{
    printf("hello from ortho_cube2\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtRotateZ(5);
    matrix_lib_p->gtRotateX(25);
    matrix_lib_p->gtRotateY(20);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube2\n");
}

void DrawLib::persp_cube()
{
    printf("hello from persp_cube\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -4);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_cube\n");
}

void DrawLib::persp_multi_cubes()
{
    printf("hello from persp_multi_cubes\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -20);
    matrix_lib_p->gtRotateZ(5);
    matrix_lib_p->gtRotateX(25);
    matrix_lib_p->gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(delta, 0, 0);
        cube();
        matrix_lib_p->gtPopMatrix();
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(0, delta, 0);
        cube();
        matrix_lib_p->gtPopMatrix();
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(0, 0, delta);
        cube();
        matrix_lib_p->gtPopMatrix();
    }    

    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_multi_cubes\n");
}
