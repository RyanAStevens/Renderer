/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.cpp
*/

// Drawing Routines, like  OpenGL
#include <matlib.h>
#include <drawlib.h>

ProjectionSetter::ProjectionSetter()
{
    this->mode = 'NULL';
}

void ProjectionSetter::setOrtho(float left, float right, float bottom, float top, float near, float far)
{
        this->mode = 'ORTHO';
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
        this->near = near;
        this->far = far;
}

void ProjectionSetter::setPerspect(float fov, float near, float far)
{
        this->mode = 'PERSPECT';
        this->fov = fov;
        this->near = near;
        this->far = far;
}

DrawLib::DrawLib(matrix_stack* mat_stack_p)
{
    
}

void DrawLib::gtOrtho(float left, float right, float bottom, float top, float near, float far)
{
    this->projMode.setOrtho(left, right, bottom, top, near, far);
}

void DrawLib::gtPerspective(float fov, float near, float far)
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
        //perfor(m transfor(mation
        vert1 = this->vertices[i];
        vert2 = this->vertices[i+1];
        vert1 = matrix_mult(matrix_stack->back(), vert1);
        vert2 = matrix_mult(matrix_stack->back(), vert2);
        
        //perform view projection
        if(this->projMode.mode == 'ORTHO')
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

void DrawLib::gtVertex(float x, float y, float z)
{
    vertices.push_back(Vertex(x, y, z);
}
