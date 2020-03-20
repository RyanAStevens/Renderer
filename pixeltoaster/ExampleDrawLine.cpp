// Fullscreen Example.
// Opens a display for fullscreen output in floating point color mode.
// Part of the PixelToaster Framebuffer Library - http://www.pixeltoaster.com

#include "PixelToaster.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265359

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

void draw_line_1(int x0, int y0, int x1, int y1)
{
    //printf("line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    int y = 0;
    float t = 0.0f;

    if(x1 < x0)
    {
        int x1_tmp = x1;
        int y1_tmp = y1;
        x1 = x0;
        y1 = y0;
        x0 = x1_tmp;
        y0 = y1_tmp;
    }

    for(int x = x0; x < x1; x++)
    {
        t = float(x - x0) / float(x1 - x0);
        y = y0 + ((y1 - y0) * t);
       // printf("x = %d, y = %d\n", x, y);
        plot_point(x, y, 1.0f, 1.0f, 1.0f);
    } 
}

void draw_line(int x0, int y0, int x1, int y1)
{
    //printf("line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    int x = 0;
    int y = 0;
    float t = 0.0f;
    float delta_t = 1.0f / width;

    if(x1 < x0)
    {
        int x1_tmp = x1;
        int y1_tmp = y1;
        x1 = x0;
        y1 = y0;
        x0 = x1_tmp;
        y0 = y1_tmp;
    }


    for(t = 0.0f; t < 1.0f; t += delta_t)
    {
        x = x0 + ((x1 - x0) * t);
        y = y0 + ((y1 - y0) * t);
        //printf("x = %d, y = %d\n", x, y);
        plot_point(x, y, 1.0f, 1.0f, 1.0f);
    } 
}

int main()
{
    Display display( "DrawLine Example", width, height, Output::Fullscreen );

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
       // printf("theta = %f\n", theta);
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
