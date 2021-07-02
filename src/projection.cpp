#include <stdio.h>
#include <projection.h>

Projection::Projection() : height(0), width(0) 
{
    printf("hello from default Projection constructor\n");
}

Projection::Projection(enum p_mode_t proj_mode, uint32_t h, uint32_t w) : height(h), width(w) 
{
    printf("hello from h/w Projection constructor\n");
    mode = proj_mode;
    matrix = new TransformMatrix(IDENTITY);
    
    //set default constraints for view volume
    left = -10.0;
    right = 10.0; 
    bottom = -10.0;
    top = 10.0;
    near = 10.0;
    far = -10.0;
     
    set_projection(proj_mode);
}

void Projection::set_projection(enum p_mode_t proj_mode)
{
    if(NULL != matrix)
    {
        delete matrix;
    }

    matrix = new TransformMatrix(IDENTITY);
    
    //Default to Orhographic Projection 
    (*matrix)[0][0] = 2.0 / (right - left);
    (*matrix)[1][1] = 2.0 / (top - bottom);
    (*matrix)[2][2] = -2.0 / (far - near);
    (*matrix)[3][0] = -1.0 * (right + left) / (right - left);
    (*matrix)[3][1] = -1.0 * (top + bottom) / (top - bottom);
    (*matrix)[3][2] = -1.0 * (far + near) / (far - near);

    if(PERSPECTIVE == proj_mode)
    {
        //Create the perspective matrix
        TransformMatrix persp_matrix(IDENTITY);
        persp_matrix[0][0] = near;
        persp_matrix[1][1] = near;
        persp_matrix[2][2] = near + far;
        persp_matrix[2][3] = -1.0 * far * near;
        persp_matrix[3][2] = 1.0;
        persp_matrix[3][3] = 0.0;

        //apply it to projection matrix
        *matrix = persp_matrix * (*matrix);
        printf("projection set to PERSPECTIVE\n");
    }
    else
    {
        printf("projection set to ORTHOGRAPHIC\n");
    }

    printf("projection matrix:\n");
    matrix->print();
    printf("\n");
    
    
}
