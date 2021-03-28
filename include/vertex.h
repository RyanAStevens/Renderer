#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector3h.h>

class Vertex: public Vector3H 
{
public:
    Vertex();
    Vertex(double x, double y, double z);
    ~Vertex();
    Vertex& operator=(Vertex rhs);
    void print();
    double x();
    double y();
    double z();
};
#endif //VERTEX_H_
