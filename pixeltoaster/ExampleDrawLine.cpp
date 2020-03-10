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

void draw_line(int x0, int y0, int x1, int y1)
{
    int y = 0;
    float t = 0.0f;
    for(int x = x0; x < x1; x++)
    {
	t = float(x - x0) / float(x1 - x0);
        y = y0 + ((y1 - y0) * t);
	plot_point(x, y, 1.0f, 0.5f, 0.25f);
    } 
}

int main()
{
    Display display( "DrawLine Example", width, height, Output::Fullscreen );

    float theta = 0.0f; 

    while ( display.open() )
    {
	set_background_color(1.0, 1.0, 1.0);

//	printf("250*-cos(theta*PI/180.0f) = %f, 250*-sin(theta*PI/180.0f) = %f, 500*cos(theta*PI/180.0f) = %f, 500*sin(theta*PI/180.0f = %f\n", 250*-cos(theta*PI/180.0f), 250*-sin(theta*PI/180.0f), 500*cos(theta*PI/180.0f), 500*sin(theta*PI/180.0f));
	draw_line(250*-cos(theta*PI/180.0f), 250*-sin(theta*PI/180.0f), 500*cos(theta*PI/180.0f), 500*sin(theta*PI/180.0f));
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
