#include <stdio.h>
#include <projection.h>

Projection::Projection() : height(0), width(0) 
{
    printf("hello from default Projection constructor\n");
}

Projection::Projection(uint32_t h, uint32_t w) : height(h), width(w) 
{
    printf("hello from h/w Projection constructor\n");
    matrix = new Matrix(IDENTITY);
    left = -1.0;
    right = 1.0; 
    bottom = -1.0;
    top = 1.0;
    near = -1.0;
    far = 1.0;
}

Orthographic::Orthographic()  
{
    printf("hello from default Orthographic constructor\n");
    mode = ORTHOGRAPHIC;
}

Orthographic::Orthographic(uint32_t h, uint32_t w) : Projection(h, w) 
{
    printf("hello from h/w Orthographic constructor\n");
    mode = ORTHOGRAPHIC;
    (*matrix)[0][0] = 2.0 / (right - left);
    (*matrix)[1][1] = 2.0 / (top - bottom);
    (*matrix)[2][2] = -2.0 / (far - near);
    (*matrix)[3][0] = -1.0 * (right + left) / (right - left);
    (*matrix)[3][1] = -1.0 * (top + bottom) / (top - bottom);
    (*matrix)[3][2] = -1.0 * (far + near) / (far - near);

}

Perspective::Perspective()  
{
    printf("hello from default Perspective constructor\n");
    mode = PERSPECTIVE;
}

Perspective::Perspective(uint32_t h, uint32_t w) : Projection(h, w) 
{
    printf("hello from h/w Perspective constructor\n");
    mode = PERSPECTIVE;
}
