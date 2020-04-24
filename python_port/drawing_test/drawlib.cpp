/* Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;
*/
// Drawing Routines, like  OpenGL
#include <matlib.h>

//Class for vertex object
class Vertices(object)
{
        self.coords = [];
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
//instantiate vertex object
vert = Vertices();

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
        vert1 = vert.coords[i];
        vert2 = vert.coords[i+1];
        vert1 = matrix_mult(myMatrix.stack[-1], vert1);
        vert2 = matrix_mult(myMatrix.stack[-1], vert2);
        
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
    vert.coords.append([[x], [y], [z], [1]]);
}
