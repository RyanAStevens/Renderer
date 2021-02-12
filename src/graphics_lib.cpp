#include <graphics_lib.h>   
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include <stack_trace.h>

GraphicsLib::GraphicsLib()
{
    printf("hello from GraphicsLib constructor\n");
}

GraphicsLib::GraphicsLib(p_mode_t draw_mode, int w, int h)
{
            printf("hello from GraphicsLib(p_mode_t draw_mode, int width, int height) constructor\n");
            width = w;
            height = h;
            n_pixels = w * h;
            printf("w %d, h %d, n_pix %d\n", width, height, n_pixels);
            image = new uint32_t[n_pixels];
            for(int i = 0; i < width*height; i++)
            {
                image[i] = 0x0000FF00;
            }
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
    printf("goodbye from set_orthographic\n");
}

void GraphicsLib::set_perspective(double fov, double near, double far)
{
    projection->fov = fov; 
    projection->near = near;
    projection->far = far;
}

void GraphicsLib::set_background_color(Color c)
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

    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	//ensure index is within bounds of the image vector
	if( index >= 0 && index < width * height)
	{
        image[index] = pixel_color;
	}
	else
	{
		printf("plot_point: ERROR point (%d, %d) is out of bounds for the current window\n", x, y);
	}
}

void GraphicsLib::draw_line(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color c)
{   
    float x_f = 0;
    float y_f = 0;
    float t = 0.0f;
    //calculate slope

if(x1 < x0 || y1 < y0)
{
    int x1_tmp = x1;
    int y1_tmp = y1;
    x1 = x0;
    y1 = y0;
    x0 = x1_tmp;
    y0 = y1_tmp;
}
            
    float m = float(y1 - y0) / float(x1 - x0);
    
    if(m <= 1 && m >= -1)
    {
        for(int x = x0; x <= x1; x++)
        {
            t = float(x - x0) / float(x1 - x0); 
            y_f = float(y0) + (float(y1 - y0) * t);
            plot_point(x, int(roundf(y_f)), c);
        }
    }
    else
    {
        for(int y = y0; y <= y1; y++)
        {
            t = float(y - y0) / float(y1 - y0); 
            x_f = float(x0) + (float(x1 - x0) * t);
            plot_point(int(roundf(x_f)), y, c);
        }
    }
}

void GraphicsLib::draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c)
{
    //implicit line eqn
    //(y0 - y1)x + (x1 - x0)y + x0y1 - x1y0 = 0
    
    double Xa = point_a.components[0];
    double Ya = point_a.components[1];
    double Xb = point_b.components[0];
    double Yb = point_b.components[1];
    double Xc = point_c.components[0];
    double Yc = point_c.components[1];
    double YaYb_diff = Ya - Yb;
    double XbXa_diff = Xb - Xa;
    double YaYc_diff = Ya - Yc;
    double XcXa_diff = Xc - Xa;
    double gamma_const = Xa*Yb - Xb*Ya;
    double beta_const = Xa*Yc - Xc*Ya;
    for ( int y = 0; y < height; ++y )
	{
	    for ( int x = 0; x < width; ++x )
	    {
            //calculate barycentric coordinates
            double gamma = ((YaYb_diff * x) + (XbXa_diff * y) + gamma_const) / 
                    ((YaYb_diff * Xc) + (XbXa_diff * Yc) + gamma_const);
            double beta = ((YaYc_diff * x) + (XcXa_diff * y) + beta_const) / 
                    ((YaYc_diff * Xb) + (XcXa_diff * Yb) + beta_const);
            double alpha = 1 - beta - gamma;
            
            if( alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1)
            {
                //point is in the triangle
                Color point_color = color_a * alpha + color_b * beta + color_c * gamma;
                plot_point(x, y, point_color);
            }
            else
            {
                //paint background
                plot_point(x, y, Color(0.1, 0.2, 0.5));
            }
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
    printf("hello from GraphicsLib::end_shape\n");
    //draw the shape
    for(int i = 0; i < vertices.size(); i += 2)
    {
        //perform transformation
        Matrix vert1 = vertices[i];
        Matrix vert2 = vertices[i+1];
        matrix_stack.initialize();
        Matrix transform = matrix_stack.get_ctm();
        vert1 = vert1*transform;
        vert2 = vert2*transform;
        
       if(NULL != projection)
       {
        //perform view projection
        if(ORTHOGRAPHIC == projection->mode)
        {
            printf("GraphicsLib::end_shape mode is ORTHOGRAPHIC\n");
            vert1[0][0] = (vert1[0][0] - projection->left)*(width/(projection->right - projection->left));
            vert1[1][0] = (vert1[1][0] - projection->bottom)*(width/(projection->top - projection->bottom));
            vert1[2][0] = 0;
            vert2[0][0] = (vert2[0][0] - projection->left)*(width/(projection->right - projection->left));
            vert2[1][0] = (vert2[1][0] - projection->bottom)*(width/(projection->top - projection->bottom));
            vert2[2][0] = 0;
        }
        else
        { // mode is perspective
            printf("GraphicsLib::end_shape mode is perspective\n");
            if(0.0 != projection->fov)
            {
                double k = tan(projection->fov*M_PI/90.0);
                if(0.0 != vert1[2][0])
                {
                    double xP1 = vert1[0][0] / abs(vert1[2][0]);
                    double yP1 = vert1[1][0] / abs(vert1[2][0]);
                    vert1[0][0] = (xP1 + k)*(width/(2*k));
                    vert1[1][0] = (yP1 + k)*(height/(2*k));
                }
                
                if(0.0 != vert2[2][0])
                {
                    double xP2 = vert2[0][0] / abs(vert2[2][0]);
                    double yP2 = vert2[1][0] / abs(vert2[2][0]);
                    vert2[0][0] = (xP2 + k)*(width/(2*k));
                    vert2[1][0] = (yP2 + k)*(height/(2*k));
                }
            }
        }
        //draw line
        printf("vert1[0][0]: %f vert1[1][0]: %f vert2[0][0]: %f vert2[1][0]: %f height: %d\n", vert1[0][0], vert1[1][0], vert2[0][0], vert2[1][0], height);
        draw_line(vert1[0][0], height - vert1[1][0], vert2[0][0], height - vert2[1][0], Color(0.0, 0.5, 1.0));
    }
    else
    {
        printf("ERROR: GraphicsLib::end_shape projection was NULL\n");
    }
    }
    printf("goodbye from GraphicsLib::end_shape\n");
}

void GraphicsLib::add_vertex(double x_in, double y_in, double z_in)
{
    Matrix v(x_in, y_in, z_in);
    vertices.push_back(v);
}

// unit radius cirle
void GraphicsLib::circle()
{
    printf("hello from circle\n");
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
    begin_shape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        add_vertex (xold, yold, 0);
        add_vertex (x, y, 0);
        xold = x;
        yold = y;
    }

    end_shape();
    printf("goodbye from circle\n");
}

void GraphicsLib::square()
{
    printf("hello from square\n");
  begin_shape ();

  add_vertex (-50, -50, 0);
  add_vertex (-50, 50, 0);
  add_vertex (-50, 50, 0);
  add_vertex (50, 50, 0);
  add_vertex (50, 50, 0);
  add_vertex (50, -50, 0);
  add_vertex (50, -50, 0);
  add_vertex (-50, -50, 0);

  end_shape();
    printf("goodbye from square\n");
}

void GraphicsLib::cube()
{
    printf("hello from cube\n");
    begin_shape();
    printf("cube: 1\n");
    
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
   
    printf("cube: 2\n");
    end_shape();
    printf("goodbye from cube\n");
}

// draw a face by transforming circles;
void GraphicsLib::face()
{
    printf("hello from face\n");
    // head
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.5, 0);
    matrix_stack.scale (0.4, 0.4, 1.0);
    circle();
    matrix_stack.pop_matrix();

    // right eye
    matrix_stack.push_matrix();
    matrix_stack.translate (0.7, 0.7, 0.0);
    matrix_stack.scale (0.1, 0.1, 1.0);
    circle();
    matrix_stack.pop_matrix();

    // // left eye
    matrix_stack.push_matrix();
    matrix_stack.translate (0.3, 0.7, 0.0);
    matrix_stack.scale (0.1, 0.1, 1.0);
    circle();
    matrix_stack.pop_matrix();

    // nose
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.5, 0.0);
    matrix_stack.scale (0.07, 0.07, 1.0);
    circle();
    matrix_stack.pop_matrix();

    // mouth
    matrix_stack.push_matrix();
    matrix_stack.translate (0.5, 0.25, 0.0);
    matrix_stack.scale (0.2, 0.1, 1.0);
    circle();
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
