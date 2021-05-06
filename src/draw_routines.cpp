#include <draw_routines.h>
#include <iostream>

// unit radius cirle
enum render_status circle(int steps, GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    double x = 0.0;
    double y = 0.0;
    double xold = 1.0;
    double yold = 0.0;
    float theta = 0.0f;
    gl_p->begin_shape();

    for(double i = 1.0; i <= steps; i+=1.0)
    {
        theta = 2.0 * 3.1415926535 * i / double(steps);
        x = cos(theta);
        y = sin(theta);
        gl_p->add_vertex (xold, yold, 0);
        gl_p->add_vertex (x, y, 0);
        xold = x;
        yold = y;
    }

    gl_p->end_shape();
      fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status square(GraphicsLib *gl_p)
{ 
  enum render_status fs = RENDER_FUNC_ERROR;
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
      fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status cube(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
        gl_p->begin_shape();
        
        // top square
        gl_p->add_vertex (-1.0, -1.0,  1.0);
        gl_p->add_vertex (-1.0,  1.0,  1.0);

        gl_p->add_vertex (-1.0,  1.0,  1.0);
        gl_p->add_vertex ( 1.0,  1.0,  1.0);

        gl_p->add_vertex ( 1.0,  1.0,  1.0);
        gl_p->add_vertex ( 1.0, -1.0,  1.0);

        gl_p->add_vertex ( 1.0, -1.0,  1.0);
        gl_p->add_vertex (-1.0, -1.0,  1.0);

        // bottom square
        gl_p->add_vertex (-1.0, -1.0, -1.0);
        gl_p->add_vertex (-1.0,  1.0, -1.0);
        
        gl_p->add_vertex (-1.0,  1.0, -1.0);
        gl_p->add_vertex ( 1.0,  1.0, -1.0);
        
        gl_p->add_vertex ( 1.0,  1.0, -1.0);
        gl_p->add_vertex ( 1.0, -1.0, -1.0);
     
        gl_p->add_vertex ( 1.0, -1.0, -1.0);
        gl_p->add_vertex (-1.0, -1.0, -1.0);
        
        // connect top to bottom
        gl_p->add_vertex (-1.0, -1.0, -1.0);
        gl_p->add_vertex (-1.0, -1.0,  1.0);
        
        gl_p->add_vertex (-1.0,  1.0, -1.0);
        gl_p->add_vertex (-1.0,  1.0,  1.0);
        
        gl_p->add_vertex ( 1.0,  1.0, -1.0);
        gl_p->add_vertex ( 1.0,  1.0,  1.0);
        
        gl_p->add_vertex ( 1.0, -1.0, -1.0);
        gl_p->add_vertex ( 1.0, -1.0,  1.0);
       
        gl_p->end_shape();
      fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

// draw a face by transforming circles;
enum render_status face(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    int circle_steps = 30;
    // head
    gl_p->push_matrix();
    gl_p->translate (0.5, 0.5, 0);
    gl_p->scale (0.4, 0.4, 1.0);
    circle(circle_steps, gl_p);
    gl_p->pop_matrix();

    // right eye
    gl_p->push_matrix();
    gl_p->translate (0.7, 0.7, 0.0);
    gl_p->scale (0.1, 0.1, 1.0);
    circle(circle_steps, gl_p);
    gl_p->pop_matrix();

    // // left eye
    gl_p->push_matrix();
    gl_p->translate (0.3, 0.7, 0.0);
    gl_p->scale (0.1, 0.1, 1.0);
    circle(circle_steps, gl_p);
    gl_p->pop_matrix();

    // nose
    gl_p->push_matrix();
    gl_p->translate (0.5, 0.5, 0.0);
    gl_p->scale (0.07, 0.07, 1.0);
    circle(circle_steps, gl_p);
    gl_p->pop_matrix();

    // mouth
    gl_p->push_matrix();
    gl_p->translate (0.5, 0.25, 0.0);
    gl_p->scale (0.2, 0.1, 1.0);
    circle(circle_steps, gl_p);
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

// draw several faces
enum render_status faces(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    //gl_p->set_orthographic (0, 1, 0, 1, -1, 1);
    
    gl_p->push_matrix();
    gl_p->translate (0.75, 0.25, 0.0);
    gl_p->scale (0.5, 0.5, 1.0);
    gl_p->translate (-0.5, -0.5, 0.0);
    face(gl_p);
    gl_p->pop_matrix();
    
    gl_p->push_matrix();
    gl_p->translate (0.25, 0.25, 0.0);
    gl_p->scale (0.5, 0.5, 1.0);
    gl_p->translate (-0.5, -0.5, 0.0);
    face(gl_p);
    gl_p->pop_matrix();
    
    gl_p->push_matrix();
    gl_p->translate (0.75, 0.75, 0.0);
    gl_p->scale (0.5, 0.5, 1.0);
    gl_p->translate (-0.5, -0.5, 0.0);
    face(gl_p);
    gl_p->pop_matrix();
    
    gl_p->push_matrix();
    gl_p->translate (0.25, 0.75, 0.0);
    gl_p->scale (0.5, 0.5, 1.0);
    gl_p->rotate_z (30);
    gl_p->translate (-0.5, -0.5, 0.0);
    face(gl_p);
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
} 

enum render_status persp_initials(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    //gl_p->set_perspective (60, -100, 100);
    gl_p->push_matrix();
    gl_p->translate(0, 0, -4);
    gl_p->rotate_z(-45);
    gl_p->rotate_x(-45);
    gl_p->rotate_y(-45);

    gl_p->begin_shape();

    //Draw R
    gl_p->add_vertex(-1, 1, 0);
    gl_p->add_vertex(0, 1, 0);

    gl_p->add_vertex(-1, 1, 0);
    gl_p->add_vertex(-1, 0.5, 0);

    gl_p->add_vertex(0, 1, 0);
    gl_p->add_vertex(0, 0.5, 0);

    gl_p->add_vertex(-1, 0.5, 0);
    gl_p->add_vertex(-1, 0, 0);

    gl_p->add_vertex(-1, 0.5, 0);
    gl_p->add_vertex(0, 0.5, 0);

    gl_p->add_vertex(-1, 0.5, 0);
    gl_p->add_vertex(0, 0, 0);

    //draw S
    gl_p->add_vertex(0.2, 0.5, 0);
    gl_p->add_vertex(1, 0.5, 0);

    gl_p->add_vertex(0.2, 0.5, 0);
    gl_p->add_vertex(0.2, 0, 0);

    gl_p->add_vertex(0.2, 0, 0);
    gl_p->add_vertex(1, 0, 0);

    gl_p->add_vertex(1, 0, 0);
    gl_p->add_vertex(1, -1, 0);

    gl_p->add_vertex(1, -1, 0);
    gl_p->add_vertex(0.2, -1, 0);

    gl_p->end_shape();
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status face_test(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->set_orthographic (0, 1, 0, 1, -1, 1);
    face(gl_p);
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status ortho_test(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->set_orthographic (-100, 100, -100, 100, -100, 100);
    square(gl_p);
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status ortho_test_scale(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->scale(1,0.5,1);
    gl_p->set_orthographic (-100, 100, -100, 100, -100, 100);
    square(gl_p);
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status ortho_test_rotate(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->rotate_z(20);
    gl_p->set_orthographic (-100, 100, -100, 100, -100, 100);
    square(gl_p);
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status ortho_cube(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->set_orthographic (-2, 2, -2, 2, -2, 2);
    gl_p->push_matrix();
    cube(gl_p);
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status ortho_cube2(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    gl_p->set_orthographic (-2, 2, -2, 2, -2, 2);
    gl_p->push_matrix();
    gl_p->rotate_z(5);
    gl_p->rotate_x(25);
    gl_p->rotate_y(20);
    cube(gl_p);
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status persp_cube(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
    //gl_p->set_perspective (60, -100, 100);
    gl_p->push_matrix();
    gl_p->translate(0, 0, -4);
    cube(gl_p);
    gl_p->pop_matrix();
    fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}

enum render_status persp_multi_cubes(GraphicsLib *gl_p)
{
  enum render_status fs = RENDER_FUNC_ERROR;
  if(NULL != gl_p)
  {
   // gl_p->set_perspective (60, -100, 100);
    gl_p->push_matrix();
    gl_p->scale(0.1, 0.1, 0.1);
    /*
    gl_p->translate(0, 0, -20);
    gl_p->rotate_z(5);
    gl_p->rotate_x(25);
    gl_p->rotate_y(20);
    */
    
    // draw several cubes in three lines (x, y, z)
    for(double delta = -6.0; delta <= 6.0; delta += 4.0)
    {
        gl_p->push_matrix();
        gl_p->translate(delta, 0, 0);
        cube(gl_p);
        gl_p->pop_matrix();
        gl_p->push_matrix();
        gl_p->translate(0, delta, 0);
        cube(gl_p);
        gl_p->pop_matrix();
        gl_p->push_matrix();
        gl_p->translate(0, 0, delta);
        cube(gl_p);
        gl_p->pop_matrix();
    }    

    gl_p->pop_matrix();
      fs = RENDER_FUNC_SUCCESS;
  }
  else
  {
     std::cout << "GraphicsLib pointer was NULL" << std::endl;
  }
  return fs;
}
