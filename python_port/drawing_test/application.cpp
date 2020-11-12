#include <application.h>
#include <matlib.h>
#include <drawlib.h>
#include <graphics_lib.h>


Application::Application()
{
    quit = false;
}

int Application::run()
{
    //printf("Hello, there from main.\n");
    MatLib matrix_lib = MatLib();
    GraphicsLib gl = GraphicsLib();
    DrawLib drawing_lib = DrawLib(&matrix_lib, &gl, window_width, window_height);
    //printf("hi 1\n");
    
    int window_width = 1000;
    int window_height = 1000;
    gl.create_window("Hello, there!", window_height, window_width, ORTHOGRAPHIC);
    
    // register listener
    gl.window->listen(this);
    //printf("hi 2\n");
    while(gl.window->open())
    {
        drawing_lib.gtBeginShape ();
     //   printf("hi 3\n");
        drawing_lib.gtVertex (250, 250, 0);
        drawing_lib.gtVertex (500, 250, 0);

        drawing_lib.gtVertex (500, 250, 0);
        drawing_lib.gtVertex (500, 500, 0);

        drawing_lib.gtVertex (500, 500, 0);
        drawing_lib.gtVertex (250, 500, 0);

        drawing_lib.gtVertex (250, 500, 0);
        drawing_lib.gtVertex (250, 250, 0);
        
        printf("hi 4\n");
        drawing_lib.gtEndShape();
        printf("hi 5\n");

        gl.window->update();
     //   printf("hi 6\n");
    }
}

void Application::onKeyDown( DisplayInterface & display, Key key )
{
        if ( key==Key::Escape )
            quit = true;

        return false;       // disable default key handlers
}

void Application::onKeyPressed( DisplayInterface & display, Key key )
{
// ...
}

void Application::onKeyUp( DisplayInterface & display, Key key )
{
// ...
}

void Application::onMouseButtonDown( DisplayInterface & display, Mouse mouse )
{
// ...
}

void Application::onMouseButtonUp( DisplayInterface & display, Mouse mouse )
{
// ...
}

void Application::onMouseMove( DisplayInterface & display, Mouse mouse )
{
// ...
}

void Application::onActivate( DisplayInterface & display, bool active )
{
// ...
}

void Application::onClose( DisplayInterface & display )
{
    return quit = true;         // returning true indicates that we want the display close to proceed
}
