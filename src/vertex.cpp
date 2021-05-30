#include <vertex.h>
#include <cstdio>

Vertex::Vertex() : Vector3H()
{
    //printf("hello from default Vertex constructor\n");

}

Vertex::Vertex(double x, double y, double z) : Vector3H(x, y, z, 1.0)
{
   // printf("Vertex(double %f, double %f, double %f) constructor\n", x, y, z);
}

Vertex::~Vertex()
{
}

Vertex& Vertex::operator=(Vertex rhs)
{
   this->components[0] = rhs.x(); 
   this->components[1] = rhs.y(); 
   this->components[2] = rhs.z(); 
   return *this;
}

double Vertex::x()
{
    return this->components[0];
}

double Vertex::y()
{
    return this->components[1];
}

double Vertex::z()
{
    return this->components[2];
}

double Vertex::h()
{
    return this->components[3];
}

void Vertex::print()
{
    printf("Vertex: (%f, %f, %f)\n", this->components[0], this->components[1], this->components[2]);
}
