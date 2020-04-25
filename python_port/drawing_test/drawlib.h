/*  
    Ryan Stevens;
    CS 3451 Computer Graphics;
    Georgia Institute of Technology;
    Spring 2017;

    file: drawlib.h
*/

// Drawing Routines, like  OpenGL

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
piblic:
    this->mode = 'NULL';
    void setOrtho(self, left, right, bottom, top, near, far);
    void setPerspect(self, fov, near, far);
}

class DrawLib
{
public:
        ProjectionSetter projMode;
        vector<Vertex> vertices;
        void gtOrtho(left, right, bottom, top, near, far);
        void gtPerspective(fov, near, far);
        void gtBeginShape();
        void gtEndShape();
        void gtVertex(x, y, z);
}
