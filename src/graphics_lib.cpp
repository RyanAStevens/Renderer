#include <graphics_lib.h>   
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <limits>

#include <stack_trace.h>

GraphicsLib::GraphicsLib(p_mode_t draw_mode, int w, int h)
{
    printf("hello from GraphicsLib(p_mode_t draw_mode, int w, int h) constructor\n");
    width = w;
    height = h;
    n_pixels = w * h;
    image = new uint32_t[n_pixels];
    projection = new Projection(draw_mode, width, height);
    printf("goodbye from GraphicsLib(p_mode_t draw_mode, int w, int h) constructor\n");

    TransformMatrix view_matrix = TransformMatrix(w, h);

    matrix_stack.get_ctm() = view_matrix * matrix_stack.get_ctm();
}

GraphicsLib::~GraphicsLib()
{
    printf("hello from GraphicsLib destructor\n");
}

void GraphicsLib::set_orthographic(double left, double right, double bottom, double top, double near, double far)
{
    printf("hello from set_orthographic\n");
    if(NULL != projection)
    {
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
    }
    else
    {
        printf("unable to set projection: projection pointer was NULL\n");
    }
    
    printf("goodbye from set_orthographic\n");
}

void GraphicsLib::set_perspective(double fov, double near, double far)
{
    projection->fov = fov; 
    projection->near = near;
    projection->far = far;
    projection->mode = PERSPECTIVE;
}

void GraphicsLib::clear_image(Color c)
{
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	for (uint32_t i = 0; i < height * width; i++)
	{
        image[i] = pixel_color;
	}
}

void GraphicsLib::begin_shape()
{
    //initialize point array
    vertices.clear();
}

void GraphicsLib::end_shape()
{
    TransformMatrix ctm = get_ctm();
    //draw the shape
    for(int i = 0; i < vertices.size(); i += 2)
    {
        //apply current transformation
        Vertex vert1 = vertices[i];
        Vertex vert2 = vertices[i+1];
        vert1 = ctm * vert1;
        vert2 = ctm * vert2;
        
        //draw line
        draw_line(vert1, vert2, Color(0.0, 0.5, 1.0));
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

void GraphicsLib::plot_point(uint32_t x, uint32_t y, Color c)
{
	uint32_t index = (y * width) + x;
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	//ensure index is within bounds of the image vector
	if( index >= 0 && index < width * height)
	{
        //printf("plot_point: (%u, %u) index=%u pixel_color=%u\n", x, y, index, pixel_color);
        image[index] = pixel_color;
	}
	else
	{
		//printf("plot_point: ERROR point (%d, %d) is out of bounds for the current window\n", x, y);
	}
}

void GraphicsLib::add_vertex(double x_in, double y_in, double z_in)
{
    Vertex v(x_in, y_in, z_in);
    vertices.push_back(v);
}

void GraphicsLib::initialize()
{
   matrix_stack.initialize();
}

void GraphicsLib::print_ctm()
{
   matrix_stack.print_ctm();
}

void GraphicsLib::translate(float x,float y,float z)
{
   matrix_stack.translate(x, y, z);
}

void GraphicsLib::scale(float x,float y,float z)
{
   matrix_stack.scale(x, y, z);
}

void GraphicsLib::rotate_x(float theta)
{
   matrix_stack.rotate_x(theta);
}

void GraphicsLib::rotate_y(float theta)
{
   matrix_stack.rotate_y(theta);
}

void GraphicsLib::rotate_z(float theta)
{
   matrix_stack.rotate_z(theta);
}

void GraphicsLib::push_matrix()
{
   matrix_stack.push_matrix();
}

void GraphicsLib::pop_matrix()
{
   matrix_stack.pop_matrix();
}

TransformMatrix& GraphicsLib::get_ctm()
{
   return matrix_stack.get_ctm();
}

int32_t GraphicsLib::size()
{
   return matrix_stack.size();
}

