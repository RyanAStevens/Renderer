#include <graphics_lib.h>
#include <window.h>
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>

GraphicsLib::GraphicsLib()
{
//    printf("hello from GraphicsLib constructor\n");
}

GraphicsLib::~GraphicsLib()
{
//    printf("hello from GraphicsLib destructor\n");
}

void GraphicsLib::create_window(const char title[], uint32_t width, uint32_t height, p_mode_t draw_mode)
{
    if(NULL != this->window)
    {
            this->window = new Window(title, width, height);
            
            switch(draw_mode)
            {
                case ORTHOGRAPHIC:
                    this->projection = new Orthographic(width, height);
                    break;
                case PERSPECTIVE:
                    this->projection = new Perspective(width, height);
                    break;
                default:
                    printf("GraphicsLib::create_window ERROR - drawing mode is not recognized");
            }
    }
    else
    {
        printf("GraphicsLib::create_window ERROR - A window already exists.");
    }
}

void GraphicsLib::set_orthographic(double left, double right, double bottom, double top, double near, double far)
{
    this->projection->left = left;
    this->projection->right = right;
    this->projection->bottom = bottom;
    this->projection->top = top; 
    this->projection->near = near;
    this->projection->far = far;
}

void GraphicsLib::set_perspective(double fov, double near, double far)
{
    this->projection->fov = fov; 
    this->projection->near = near;
    this->projection->far = far;
}

void GraphicsLib::set_background_color(float r, float g, float b)
{
	unsigned int index = 0;

	for ( int y = 0; y < this->window->height; ++y )
	{
	    for ( int x = 0; x < this->window->width; ++x )
	    {
        this->window->image[index].r = r;
		this->window->image[index].g = g;
		this->window->image[index].b = b;

		++index;
	    }
	}
}

void GraphicsLib::plot_point(int x, int y, Color c)
{
    //printf("plot_point: (%d, %d)\n", x, y);
	int index = (x * this->window->width) + y;
	
	//ensure index is within bounds of the this->window->image vector
	if( index >= 0 && index < this->window->width * this->window->height)
	{
		this->window->image[index].r = c.r;
		this->window->image[index].g = c.g;
		this->window->image[index].b = c.b;
	}
	else
	{
		printf("plot_point: ERROR point (%d, %d) is out of bounds for the current window->\n", x, y);
	}
}

void GraphicsLib::draw_line(int x0, int y0, int x1, int y1)
{   
    printf("draw_line: x0 = %d, y0 = %d, x1 = %d, y1 = %d\n", x0, y0, x1, y1);
    float x_f = 0;
    float y_f = 0;
    float t = 0.0f;
    //calculate slope
    float m = float(y1 - y0) / float(x1 - x0);

        if(x1 < x0 || y1 < y0)
        {
            int x1_tmp = x1;
            int y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }
    
    if(m <= 1 && m >= -1)
    {
        for(int x = x0; x <= x1; x++)
        {
            t = float(x - x0) / float(x1 - x0); 
            y_f = float(y0) + (float(y1 - y0) * t);
            plot_point(x, int(roundf(y_f)), Color(1.0f, 1.0f, 1.0f));
        }
    }
    else
    {
        for(int y = y0; y <= y1; y++)
        {
            t = float(y - y0) / float(y1 - y0); 
            x_f = float(x0) + (float(x1 - x0) * t);
            plot_point(int(roundf(x_f)), y, Color(1.0f, 1.0f, 1.0f));
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
    for ( int y = 0; y < this->window->height; ++y )
	{
	    for ( int x = 0; x < this->window->width; ++x )
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
