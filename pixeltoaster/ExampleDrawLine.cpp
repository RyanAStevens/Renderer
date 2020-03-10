// Fullscreen Example.
// Opens a display for fullscreen output in floating point color mode.
// Part of the PixelToaster Framebuffer Library - http://www.pixeltoaster.com

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
	int index = (x * width) + y;

	pixels[index].r = r;
	pixels[index].g = g;
	pixels[index].b = b;
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

    while ( display.open() )
    {
	set_background_color(1.0, 1.0, 1.0);
	draw_line(250, 250, 500, 500);
	display.update( pixels );
    }
}
