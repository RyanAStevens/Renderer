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

//Class to keep track of projection settings
class ProjectionSetter(object)
{
    this->mode = 'NULL';

    void setOrtho(self, left, right, bottom, top, near, far)
    {
        self.mode = 'ORTHO';
        self.left = left;
        self.right = right;
        self.bottom = bottom;
        self.top = top;
        self.near = near;
        self.far = far;
    }
    
    void setPerspect(self, fov, near, far)
    {
        self.mode = 'PERSPECT';
        self.fov = fov;
        self.near = near;
        self.far = far;
    }
}

//instantiate projection object    
projMode = ProjectionSetter();

vector<Vertex> vertices;

void gtOrtho(left, right, bottom, top, near, far)
{
    projMode.setOrtho(left, right, bottom, top, near, far);
}

void gtPerspective(fov, near, far)
{
    projMode.setPerspect(fov, near, far);
}    

void gtBeginShape()
{
    //initialize point array
    vert.coords = [];
}

void gtEndShape()
{
    //draw the shape
    for( i in range(0,len(vert.coords),2))
    {
        //perfor(m transfor(mation
        Vertex vert1 = vert.coords[i];
        Vertex vert2 = vert.coords[i+1];
        Vertex vert1 = matrix_mult(myMatrix.stack[-1], vert1);
        Vertex vert2 = matrix_mult(myMatrix.stack[-1], vert2);
        
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
            k = math.tan(projMode.fov*math.pi/180/2.0);
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

void gtVertex(x, y, z)
{
    vertices.push_back(Vertex(x, y, z);
}
