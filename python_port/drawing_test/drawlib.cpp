/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.cpp
*/

// Drawing Routines, like  OpenGL
#include <matlib.h>

//Class for vertex object
class Vertex
{
    public:
    float x, y, z;
    const int h = 1;
};

ProjectionSetter::ProjectionSetter()
{
    this->mode = 'NULL';
}

void ProjectionSetter::setOrtho(self, left, right, bottom, top, near, far)
{
        self.mode = 'ORTHO';
        self.left = left;
        self.right = right;
        self.bottom = bottom;
        self.top = top;
        self.near = near;
        self.far = far;
}

void ProjectionSetter::setPerspect(self, fov, near, far)
{
        self.mode = 'PERSPECT';
        self.fov = fov;
        self.near = near;
        self.far = far;
}

/*
DrawLib::DrawLib()
{
}
*/

void DrawLib::gtOrtho(left, right, bottom, top, near, far)
{
    projMode.setOrtho(left, right, bottom, top, near, far);
}

void DrawLib::gtPerspective(fov, near, far)
{
    projMode.setPerspect(fov, near, far);
}    

void DrawLib::gtBeginShape()
{
    //initialize point array
    this->vertices.clear();
}

void DrawLib::gtEndShape()
{
    //draw the shape
    for(int i = 0; i <= this->vertices.size(); i += 2)
    {
        //perfor(m transfor(mation
        Vertex vert1 = this->vertices[i];
        Vertex vert2 = this->vertices[i+1];
        Vertex vert1 = matrix_mult(myMatrix.stack.back(), vert1);
        Vertex vert2 = matrix_mult(myMatrix.stack.back(), vert2);
        
        //perform view projection
        if(projMode.mode == 'ORTHO')
        {
            vert1[0][0] = (vert1[0][0] - projMode.left)*(width/(projMode.right - projMode.left));
            vert1[1][0] = (vert1[1][0] - projMode.bottom)*(width/(projMode.top - projMode.bottom));
            vert1[2][0] = 0;
            vert2[0][0] = (vert2[0][0] - projMode.left)*(width/(projMode.right - projMode.left));
            vert2[1][0] = (vert2[1][0] - projMode.bottom)*(width/(projMode.top - projMode.bottom));
            vert2[2][0] = 0;
        }
        else
        { // mode is perspective
            k = tan(projMode.fov*M_PI/180/2.0);
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

void DrawLib::gtVertex(x, y, z)
{
    vertices.push_back(Vertex(x, y, z);
}
