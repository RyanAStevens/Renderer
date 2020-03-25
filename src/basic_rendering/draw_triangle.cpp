#include "PixelToaster.h"
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

void plot_point(int x, int y, float r, float g, float b)
{
    //printf("plot_point: (%d, %d)\n", x, y);
	int index = (x * width) + y;
	
	//ensure index is within bounds of the pixels vector
	if( index >= 0 && index < width * height)
	{
		pixels[index].r = r;
		pixels[index].g = g;
		pixels[index].b = b;
	}
	else
	{
		printf("plot_point: ERROR point (%d, %d) does not exist.\n", x, y);
	}
}

void draw_triangle(float p1, float p2, float p3)
{
    //implicit line eqn
    //(y0 - y1)x + (x1 - x0)y + x0y1 - x1y0 = 0
    
    //calculate barycentric coordinates
    alpha = ;
    beta = ;
    gamma = ;
} 

int main()
{
    Display display( "draw_triangle", width, height, Output::Fullscreen );

    float theta = 0.0f; 
    float half_w = width / 2;
    float half_h = height / 2;
    float con_rad = PI / 180.0f;
    float theta_rad = 0.0f;

    while ( display.open() )
    {
        set_background_color(0.1, 0.2, 0.5);
        
        theta_rad = theta * con_rad;
        draw_line(half_w * (cos(theta_rad + PI) + 1), half_h * (sin(theta_rad + PI) + 1), half_w * (cos(theta_rad)+1), half_h *(sin(theta_rad)+1));
        display.update( pixels );
        if(theta < 360.0f)
        {
            theta++;
        }
        else
        {
            theta = 0.0f;
        }
    }
}
