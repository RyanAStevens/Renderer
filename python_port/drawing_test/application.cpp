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
    printf("Hello, app::run()\n");
    int window_width = 1000;
    int window_height = 1000;
    
    MatLib matrix_lib = MatLib();
   
    GraphicsLib gl = GraphicsLib();
   
    DrawLib drawing_lib = DrawLib(&matrix_lib, &gl, window_width, window_height);
    
    gl.create_window("Boom, Flip it!", window_height, window_width, ORTHOGRAPHIC);
    
    // register listener
    gl.window->listen(this);
    while(gl.window->open())
    {
        drawing_lib.gtBeginShape ();
        drawing_lib.gtVertex (250, 250, 0);
        drawing_lib.gtVertex (500, 250, 0);

        drawing_lib.gtVertex (500, 250, 0);
        drawing_lib.gtVertex (500, 500, 0);

        drawing_lib.gtVertex (500, 500, 0);
        drawing_lib.gtVertex (250, 500, 0);

        drawing_lib.gtVertex (250, 500, 0);
        drawing_lib.gtVertex (250, 250, 0);
        
        drawing_lib.gtEndShape();

        gl.window->update();
    }
}

void Application::onKeyDown( PixelToaster::DisplayInterface & display, PixelToaster::Key key )
{
        if ( key==PixelToaster::Key::Escape )
        {
            quit = true;
        }
        else
        {
            printf("you pressed a key!!!\n");
        }
}

void Application::onKeyPressed( PixelToaster::DisplayInterface & display, PixelToaster::Key key )
{
// ...
}

void Application::onKeyUp( PixelToaster::DisplayInterface & display, PixelToaster::Key key )
{
// ...
}

void Application::onMouseButtonDown( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse )
{
// ...
}

void Application::onMouseButtonUp( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse )
{
// ...
}

void Application::onMouseMove( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse )
{
// ...
}

void Application::onActivate( PixelToaster::DisplayInterface & display, bool active )
{
// ...
}

bool Application::onClose( PixelToaster::DisplayInterface & display )
{
    return quit = true;         // returning true indicates that we want the display close to proceed
}
