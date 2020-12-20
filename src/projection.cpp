#include <stdio.h>
#include <projection.h>

Projection::Projection() : height(0), width(0) 
{
    printf("hello from default Projection constructor\n");
}

Projection::Projection(uint32_t h, uint32_t w) : height(h), width(w) 
{
    printf("hello from h/w Projection constructor\n");
}

Orthographic::Orthographic()  
{
    printf("hello from default Orthographic constructor\n");
    this->mode = ORTHOGRAPHIC;
}

Orthographic::Orthographic(uint32_t h, uint32_t w) : Projection(h, w) 
{
    printf("hello from h/w Orthographic constructor\n");
    this->mode = ORTHOGRAPHIC;
}

Perspective::Perspective()  
{
    printf("hello from default Perspective constructor\n");
    this->mode = PERSPECTIVE;
}

Perspective::Perspective(uint32_t h, uint32_t w) : Projection(h, w) 
{
    printf("hello from h/w Perspective constructor\n");
    this->mode = PERSPECTIVE;
}

void Orthographic::project_vertex(Vector3 v)
{
    v.components[0] = (v.components[0] - left)*(width/(right - left));
    v.components[1] = (v.components[1] - bottom)*(width/(top - bottom));
    //v.components[0] = (v.components[0] - this->projection.left)*(this->projection.width/(this->projection.right - this->projection.left))
    //v.components[1] = (v.components[1] - this->projection.bottom)*(this->projection.width/(this->projection.top - this->projection.bottom))
}

void Perspective::project_vertex(Vector3)
{
}
