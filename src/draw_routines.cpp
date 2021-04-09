#include <draw_routines.h>
#include <iostream>

/*
// unit radius cirle
void circle(int steps)
{
    double x = 0.0;
    double y = 0.0;
    double xold = 1.0;
    double yold = 0.0;
    float theta = 0.0f;
    begin_shape();

    for(double i = 1.0; i <= steps; i+=1.0)
    {
        theta = 2.0 * 3.1415926535 * i / double(steps);
        x = cos(theta);
        y = sin(theta);
        add_vertex (xold, yold, 0);
        add_vertex (x, y, 0);
        xold = x;
        yold = y;
    }

    end_shape();
}
*/
void square(GraphicsLib *gl_p)
{
  if(NULL != gl_p)
  {
      gl_p->begin_shape ();

      gl_p->add_vertex (-0.5, -0.5, 0);
      gl_p->add_vertex (0.5, -0.5, 0);
      gl_p->add_vertex (0.5, -0.5, 0);
      gl_p->add_vertex (0.5, 0.5, 0);
      gl_p->add_vertex (0.5, 0.5, 0);
      gl_p->add_vertex (-0.5, 0.5, 0);
      gl_p->add_vertex (-0.5, 0.5, 0);
      gl_p->add_vertex (-0.5, -0.5, 0);

      gl_p->end_shape();
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
}
/*
void cube()
{
        begin_shape();
        
        // top square
        add_vertex (-1.0, -1.0,  1.0);
        add_vertex (-1.0,  1.0,  1.0);

        add_vertex (-1.0,  1.0,  1.0);
        add_vertex ( 1.0,  1.0,  1.0);

        add_vertex ( 1.0,  1.0,  1.0);
        add_vertex ( 1.0, -1.0,  1.0);

        add_vertex ( 1.0, -1.0,  1.0);
        add_vertex (-1.0, -1.0,  1.0);

        // bottom square
        add_vertex (-1.0, -1.0, -1.0);
        add_vertex (-1.0,  1.0, -1.0);
        
        add_vertex (-1.0,  1.0, -1.0);
        add_vertex ( 1.0,  1.0, -1.0);
        
        add_vertex ( 1.0,  1.0, -1.0);
        add_vertex ( 1.0, -1.0, -1.0);
     
        add_vertex ( 1.0, -1.0, -1.0);
        add_vertex (-1.0, -1.0, -1.0);
        
        // connect top to bottom
        add_vertex (-1.0, -1.0, -1.0);
        add_vertex (-1.0, -1.0,  1.0);
        
        add_vertex (-1.0,  1.0, -1.0);
        add_vertex (-1.0,  1.0,  1.0);
        
        add_vertex ( 1.0,  1.0, -1.0);
        add_vertex ( 1.0,  1.0,  1.0);
        
        add_vertex ( 1.0, -1.0, -1.0);
        add_vertex ( 1.0, -1.0,  1.0);
       
        end_shape();
}

// draw a face by transforming circles;
void face()
{
    int circle_steps = 50;
    printf("hello from face\n");
    // head
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.5, 0);
    matrix_stack.scale (0.4, 0.4, 1.0);
    circle(circle_steps);
    matrix_stack.pop_matrix();

    // right eye
    matrix_stack.push_matrix();
    matrix_stack.translate (0.7, 0.7, 0.0);
    matrix_stack.scale (0.1, 0.1, 1.0);
    circle(circle_steps);
    matrix_stack.pop_matrix();

    // // left eye
    matrix_stack.push_matrix();
    matrix_stack.translate (0.3, 0.7, 0.0);
    matrix_stack.scale (0.1, 0.1, 1.0);
    circle(circle_steps);
    matrix_stack.pop_matrix();

    // nose
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.5, 0.0);
    matrix_stack.scale (0.07, 0.07, 1.0);
    circle(circle_steps);
    matrix_stack.pop_matrix();

    // mouth
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.25, 0.0);
    matrix_stack.scale (0.2, 0.1, 1.0);
    circle(circle_steps);
    matrix_stack.pop_matrix();
    printf("goodbye from face\n");
}

// draw several faces
void faces()
{
    printf("hello from faces\n");
    matrix_stack.initialize ();
    
    set_orthographic (0, 1, 0, 1, -1, 1);
    
    matrix_stack.push_matrix();
    matrix_stack.translate (0.75, 0.25, 0.0);
    matrix_stack.scale (0.5, 0.5, 1.0);
    matrix_stack.translate (-0.5, -0.5, 0.0);
    face();
    matrix_stack.pop_matrix();
    
    matrix_stack.push_matrix();
    matrix_stack.translate (0.25, 0.25, 0.0);
    matrix_stack.scale (0.5, 0.5, 1.0);
    matrix_stack.translate (-0.5, -0.5, 0.0);
    face();
    matrix_stack.pop_matrix();
    
    matrix_stack.push_matrix();
    matrix_stack.translate (0.75, 0.75, 0.0);
    matrix_stack.scale (0.5, 0.5, 1.0);
    matrix_stack.translate (-0.5, -0.5, 0.0);
    face();
    matrix_stack.pop_matrix();
    
    matrix_stack.push_matrix();
    matrix_stack.translate (0.25, 0.75, 0.0);
    matrix_stack.scale (0.5, 0.5, 1.0);
    matrix_stack.rotate_z (30);
    matrix_stack.translate (-0.5, -0.5, 0.0);
    face();
    matrix_stack.pop_matrix();
    printf("goodbye from faces\n");
} 

void persp_initials()
{
    printf("hello from persp_initials\n");
    matrix_stack.initialize();
    set_perspective (60, -100, 100);
    matrix_stack.push_matrix();
    matrix_stack.translate(0, 0, -4);
    matrix_stack.rotate_z(-45);
    matrix_stack.rotate_x(-45);
    matrix_stack.rotate_y(-45);

    begin_shape();

    //Draw R
    add_vertex(-1, 1, 0);
    add_vertex(0, 1, 0);

    add_vertex(-1, 1, 0);
    add_vertex(-1, 0.5, 0);

    add_vertex(0, 1, 0);
    add_vertex(0, 0.5, 0);

    add_vertex(-1, 0.5, 0);
    add_vertex(-1, 0, 0);

    add_vertex(-1, 0.5, 0);
    add_vertex(0, 0.5, 0);

    add_vertex(-1, 0.5, 0);
    add_vertex(0, 0, 0);

    //draw S
    add_vertex(0.2, 0.5, 0);
    add_vertex(1, 0.5, 0);

    add_vertex(0.2, 0.5, 0);
    add_vertex(0.2, 0, 0);

    add_vertex(0.2, 0, 0);
    add_vertex(1, 0, 0);

    add_vertex(1, 0, 0);
    add_vertex(1, -1, 0);

    add_vertex(1, -1, 0);
    add_vertex(0.2, -1, 0);

    end_shape();
    matrix_stack.pop_matrix();
    printf("goodbye from persp_initials\n");
}

void face_test()
{
    printf("hello from face_test\n");
    matrix_stack.initialize();
    set_orthographic (0, 1, 0, 1, -1, 1);
    face();
    printf("goodbye from face_test\n");
}

void ortho_test()
{
    printf("hello from ortho_test\n");
    matrix_stack.initialize();
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test\n");
}

void ortho_test_scale()
{
    printf("hello from ortho_test_scale\n");
    matrix_stack.initialize();
    matrix_stack.scale(1,0.5,1);
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_scale\n");
}

void ortho_test_rotate()
{
    printf("hello from ortho_test_rotate\n");
    matrix_stack.initialize();
    matrix_stack.rotate_z(20);
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_rotate\n");
}

void ortho_cube()
{
    printf("hello from ortho_cube\n");
    matrix_stack.initialize();
    set_orthographic (-2, 2, -2, 2, -2, 2);
    matrix_stack.push_matrix();
    matrix_stack.rotate_y(17);
    cube();
    matrix_stack.pop_matrix();
    printf("goodbye from ortho_cube\n");
}

void ortho_cube2()
{
    printf("hello from ortho_cube2\n");
    matrix_stack.initialize();
    set_orthographic (-2, 2, -2, 2, -2, 2);
    matrix_stack.push_matrix();
    matrix_stack.rotate_z(5);
    matrix_stack.rotate_x(25);
    matrix_stack.rotate_y(20);
    cube();
    matrix_stack.pop_matrix();
    printf("goodbye from ortho_cube2\n");
}

void persp_cube()
{
    printf("hello from persp_cube\n");
    matrix_stack.initialize();
    set_perspective (60, -100, 100);
    matrix_stack.push_matrix();
    matrix_stack.translate(0, 0, -4);
    cube();
    matrix_stack.pop_matrix();
    printf("goodbye from persp_cube\n");
}

void persp_multi_cubes()
{
    printf("hello from persp_multi_cubes\n");
    matrix_stack.initialize();
    set_perspective (60, -100, 100);
    matrix_stack.push_matrix();
    matrix_stack.translate(0, 0, -20);
    matrix_stack.rotate_z(5);
    matrix_stack.rotate_x(25);
    matrix_stack.rotate_y(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        matrix_stack.push_matrix();
        matrix_stack.translate(delta, 0, 0);
        cube();
        matrix_stack.pop_matrix();
        matrix_stack.push_matrix();
        matrix_stack.translate(0, delta, 0);
        cube();
        matrix_stack.pop_matrix();
        matrix_stack.push_matrix();
        matrix_stack.translate(0, 0, delta);
        cube();
        matrix_stack.pop_matrix();
    }    

    matrix_stack.pop_matrix();
    printf("goodbye from persp_multi_cubes\n");
}
*/
