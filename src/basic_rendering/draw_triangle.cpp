#include <PixelToaster.h>
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>

using namespace PixelToaster;

const int width = 1000;
const int height = 1000;

vector<Pixel> pixels( width * height );

void set_background_color(float r, float g, float b)
{
	unsigned int index = 0;

	for ( int y = 0; y < height; ++y )
	{
	    for ( int x = 0; x < width; ++x )
	    {
		pixels[index].r = r;
		pixels[index].g = g;
		pixels[index].b = b;

		++index;
	    }
	}
}

void plot_point(int x, int y, Color c)
{
    //printf("plot_point: (%d, %d)\n", x, y);
	int index = (x * width) + y;
	
	//ensure index is within bounds of the pixels vector
	if( index >= 0 && index < width * height)
	{
		pixels[index].r = c.r;
		pixels[index].g = c.g;
		pixels[index].b = c.b;
	}
	else
	{
		printf("plot_point: ERROR point (%d, %d) does not exist.\n", x, y);
	}
}

void draw_triangle(Vector2 a, Color a_color, Vector2 b, Color b_color, Vector2 c, Color c_color)
{
    //implicit line eqn
    //(y0 - y1)x + (x1 - x0)y + x0y1 - x1y0 = 0
    
    double Xa = a.components[0];
    double Ya = a.components[1];
    double Xb = b.components[0];
    double Yb = b.components[1];
    double Xc = c.components[0];
    double Yc = c.components[1];
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
                Color point_color = a_color * alpha + b_color * beta + c_color * gamma;
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

int main()
{
    Display display( "draw_triangle", width, height, Output::Fullscreen );

    float theta = 0.0f; 
    float half_w = width / 2;
    float half_h = height / 2;
    float con_rad = M_PI / 180.0f;
    float theta_rad = 0.0f;

    while ( display.open() )
    {
       Vector2 A(250.0f, 250.0f);
       Color A_color(1.0, 0.0, 0.0);
       Vector2 B(150.0f, 750.0f);
       Color B_color(0.0, 1.0, 0.0);
       Vector2 C(350.0f, 750.0f);
       Color C_color(0.0, 0.0, 1.0);

       draw_triangle(A, A_color, B, B_color, C, C_color);

       /*     
        theta_rad = theta * con_rad;
        draw_line(half_w * (cos(theta_rad + PI) + 1), half_h * (sin(theta_rad + PI) + 1), half_w * (cos(theta_rad)+1), half_h *(sin(theta_rad)+1));
        if(theta < 360.0f)
        {
            theta++;
        }
        else
        {
            theta = 0.0f;
        }
       */ 
        display.update( pixels );
    }
}
