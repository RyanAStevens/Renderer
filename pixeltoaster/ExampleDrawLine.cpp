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

void draw_line_2(int x0, int y0, int x1, int y1)
{
    printf("line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    float x_f = 0;
    float y_f = 0;
    float t = 0.0f;
    //calculate slope
    float m = float(y1 - y0) / float(x1 - x0);
    //printf("m: %f, (y1 - y0): %f (x1 - x0): %f\n", m, float(y1 - y0), float(x1 - x0));

    if(m <= 1 && m >= -1)
    {
        if(x1 < x0)
        {
            int x1_tmp = x1;
            int y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }
        printf("draw_line_2: loop x slope: %f\n", m);
        for(int x = x0; x <= x1; x++)
        {
            t = float(x - x0) / float(x1 - x0);
            y_f = float(y0) + (float(y1 - y0) * t);
           // printf("x = %d, y = %d\n", x, y);
            plot_point(x, int(roundf(y_f)), 1.0f, 1.0f, 1.0f);
        } 
    }
    else
    {
        if(y1 < y0)
        {
            int x1_tmp = x1;
            int y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }
        printf("draw_line_2:Y_LOOP slope: %f\n", m);
        for(int y = y0; y <= y1; y++)
        {   
     //       printf("y: %d\n", y);
            t = float(y - y0) / float(y1 - y0);
            x_f = float(x0) + (float(x1 - x0) * t);
           // printf("x = %d, y = %d\n", x, y);
            plot_point(int(roundf(x_f)), y, 1.0f, 1.0f, 1.0f);
        } 
    }
}

void draw_line_1(int x0, int y0, int x1, int y1)
{
    //printf("line from (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    float y = 0;
    float t = 0.0f;

    for(int x = x0; x <= x1; x++)
    {
        t = float(x - x0) / float(x1 - x0);
        y = float(y0) + (float(y1 - y0) * t);
       // printf("x = %d, y = %d\n", x, y);
        plot_point(x, roundf(y), 1.0f, 1.0f, 1.0f);
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
        
        printf("theta = %f\n", theta);
        theta_rad = theta * con_rad;
        draw_line_2(half_w * (cos(theta_rad + PI) + 1), half_h * (sin(theta_rad + PI) + 1), half_w * (cos(theta_rad)+1), half_h *(sin(theta_rad)+1));
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
