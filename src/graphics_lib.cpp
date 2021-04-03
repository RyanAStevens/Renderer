#include <graphics_lib.h>   
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <limits>

#include <stack_trace.h>

GraphicsLib::GraphicsLib()
{
    printf("hello from GraphicsLib constructor\n");
}

GraphicsLib::GraphicsLib(p_mode_t draw_mode, int w, int h)
{
            //printf("hello from GraphicsLib(p_mode_t draw_mode, int width, int height) constructor\n");
            width = w;
            height = h;
            n_pixels = w * h;
            //printf("w %d, h %d, n_pix %d\n", width, height, n_pixels);
            image = new uint32_t[n_pixels];
            switch(draw_mode)
            {
                case ORTHOGRAPHIC:
                    projection = new Orthographic(width, height);
                    break;
                case PERSPECTIVE:
                    projection = new Perspective(width, height);
                    break;
                default:
                    printf("GraphicsLib constructor ERROR - drawing mode is not recognized");
            }
}

GraphicsLib::~GraphicsLib()
{
    printf("hello from GraphicsLib destructor\n");
    /*
    delete[] image;
    delete vertices;
    delete matrix_stack;
    delete projection;
    */
}

void GraphicsLib::set_orthographic(double left, double right, double bottom, double top, double near, double far)
{
    printf("hello from set_orthographic\n");
    projection->left = left;
    projection->right = right;
    projection->bottom = bottom;
    projection->top = top; 
    projection->near = near;
    projection->far = far;

    //scale
    (*projection->matrix)[0][0] = 2 / (right - left);
    (*projection->matrix)[1][1] = 2 / (top - bottom);
    (*projection->matrix)[2][2] = -2 / (far - near);

    //translate
    (*projection->matrix)[0][3] = -1 * (right + left) / (right - left);
    (*projection->matrix)[1][3] = -1 * (top + bottom) / (top - bottom);
    (*projection->matrix)[2][3] = -1 * (far + near) / (far - near);
    
    printf("goodbye from set_orthographic\n");
}

void GraphicsLib::set_perspective(double fov, double near, double far)
{
    projection->fov = fov; 
    projection->near = near;
    projection->far = far;
}

void GraphicsLib::clear_image(Color c)
{
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	for (uint32_t i = 0; i < height * width; i++)
	{
        image[i] = pixel_color;
	}
}

void GraphicsLib::plot_point(uint32_t x, uint32_t y, Color c)
{
	uint32_t index = (y * width) + x;
    //printf("plot_point: x = %u y = %u index = %u\n", x, y, index);
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	//ensure index is within bounds of the image vector
	if( index >= 0 && index < width * height)
	{
        //printf("plot_point: (%u, %u) index=%u pixel_color=%u\n", x, y, index, pixel_color);
        image[index] = pixel_color;
	}
	else
	{
		printf("plot_point: ERROR point (%d, %d) is out of bounds for the current window\n", x, y);
	}
}

void GraphicsLib::draw_line(Vertex vert1, Vertex vert2, Color c)
{   
    double m = 0;
    double x_f = 0;
    double y_f = 0;
    double t = 0.0f;

    double x0 = vert1.x();
    double y0 = vert1.y();
    double x1 = vert2.x();
    double y1 = vert2.y();
   
       
    //map points to screen space
    x0 = (x0+1.0)*width/2.0; 
    y0 = (y0+1.0)*height/2.0;
    x1 = (x1+1.0)*width/2.0; 
    y1 = (y1+1.0)*height/2.0;
    
    //calculate slope
    if(x0 == x1)
    {
        //vertical line, infinite slope
        m = std::numeric_limits<double>::max();
    }
    else
    {
        m = (y1 - y0) / (x1 - x0);
    }
    
    if(m <= 1 && m >= -1)
    {
        //printf("draw_line slope between [-1:1] inclusive: x0 = %f y0 = %f x1 = %f y1 = %f m = %f\n", x0, y0, x1, y1, m);

        //swap order if needed
        if(x1 < x0)
        {
            double x1_tmp = x1;
            double y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }

        for(double x = x0; x <= x1; x++)
        {
            t = (x - x0) / (x1 - x0); 
            y_f = y0 + ((y1 - y0) * t);
            //map points to screen space

            plot_point(int(x), int(y_f), c);
        }
    }
    else
    {
        //printf("draw_line: x0 = %f y0 = %f x1 = %f y1 = %f m = %f\n", x0, y0, x1, y1, m);
        
        //swap order if needed
        if(y1 < y0)
        {
            double x1_tmp = x1;
            double y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }
       
       for(double y = y0; y <= y1; y++)
        {
            t = (y - y0) / (y1 - y0); 
            x_f = x0 + ((x1 - x0) * t);
            plot_point(int(x_f), int(y), c);
        }
    }
}

void GraphicsLib::begin_shape()
{
    //initialize point array
    vertices.clear();
}

void GraphicsLib::end_shape()
{
        if(NULL != projection)
        {
            TransformMatrix inv_m(INVERT_Y);
            //draw the shape
            for(int i = 0; i < vertices.size(); i += 2)
            {
                //perform transformation
                Vertex vert1 = vertices[i];
                Vertex vert2 = vertices[i+1];
                /*
                printf("\n\nend_shape: before transformation\n");
                vert1.print();
                vert2.print();
                */
                TransformMatrix ctm = matrix_stack.get_ctm();
                vert1 = ctm * (*projection->matrix) * inv_m * vert1;
                vert2 = ctm * (*projection->matrix) * inv_m * vert2;
                /*
                printf("end_shape: after transformation\n");
                vert1.print();
                vert2.print();
                printf("\n\n");
                */

                //draw line
                draw_line(vert1, vert2, Color(0.0, 0.5, 1.0));
            }
        }
        else
        {
            printf("ERROR: GraphicsLib::end_shape projection was NULL\n");
        }
}

void GraphicsLib::add_vertex(double x_in, double y_in, double z_in)
{
    Vertex v(x_in, y_in, z_in);
    vertices.push_back(v);
}

// unit radius cirle
void GraphicsLib::circle(int steps)
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

void GraphicsLib::square()
{
  begin_shape ();

  add_vertex (-0.5, -0.5, 0);
  add_vertex (0.5, -0.5, 0);
  add_vertex (0.5, -0.5, 0);
  add_vertex (0.5, 0.5, 0);
  add_vertex (0.5, 0.5, 0);
  add_vertex (-0.5, 0.5, 0);
  add_vertex (-0.5, 0.5, 0);
  add_vertex (-0.5, -0.5, 0);

  end_shape();
}

void GraphicsLib::cube()
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
void GraphicsLib::face()
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
void GraphicsLib::faces()
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

void GraphicsLib::persp_initials()
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

void GraphicsLib::face_test()
{
    printf("hello from face_test\n");
    matrix_stack.initialize();
    set_orthographic (0, 1, 0, 1, -1, 1);
    face();
    printf("goodbye from face_test\n");
}

void GraphicsLib::ortho_test()
{
    printf("hello from ortho_test\n");
    matrix_stack.initialize();
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test\n");
}

void GraphicsLib::ortho_test_scale()
{
    printf("hello from ortho_test_scale\n");
    matrix_stack.initialize();
    matrix_stack.scale(1,0.5,1);
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_scale\n");
}

void GraphicsLib::ortho_test_rotate()
{
    printf("hello from ortho_test_rotate\n");
    matrix_stack.initialize();
    matrix_stack.rotate_z(20);
    set_orthographic (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_rotate\n");
}

void GraphicsLib::ortho_cube()
{
    printf("hello from ortho_cube\n");
    matrix_stack.initialize();
    printf("ortho_cube 1\n");
    set_orthographic (-2, 2, -2, 2, -2, 2);
    printf("ortho_cube 2\n");
    matrix_stack.push_matrix();
    printf("ortho_cube 3\n");
    matrix_stack.rotate_y(17);
    printf("ortho_cube 4\n");
    cube();
    printf("ortho_cube 5\n");
    matrix_stack.pop_matrix();
    printf("goodbye from ortho_cube\n");
}

void GraphicsLib::ortho_cube2()
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

void GraphicsLib::persp_cube()
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

void GraphicsLib::persp_multi_cubes()
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
