#include <application.h>
#include <matlib.h>
#include <drawlib.h>
#include <graphics_lib.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

Application::Application()
{
    this->dl = new DrawLib(new MatLib(), new GraphicsLib(), WINDOW_WIDTH, WINDOW_HEIGHT);
    quit = false;
}

int Application::run()
{
    dl->create_window("Boom, Flip it!", WINDOW_HEIGHT, WINDOW_WIDTH, ORTHOGRAPHIC);
    
    // register listener
    dl->listen_window(this);
    while(dl->window_open())
    {
        dl->update_window();
    }
    return 0;
}

void Application::onKeyDown( PixelToaster::DisplayInterface & display, PixelToaster::Key key )
{
    switch(key)
    {
            case PixelToaster::Key::One:
                ortho_test();
                break;
            case PixelToaster::Key::Two:
                ortho_test_scale();
                break;
            case PixelToaster::Key::Three:
                ortho_test_rotate();
                break;
            case PixelToaster::Key::Four:
                face_test();
                break;
            case PixelToaster::Key::Five:
                faces();
                break;
            case PixelToaster::Key::Six:
                ortho_cube();
                break;
            case PixelToaster::Key::Seven:
                ortho_cube2();
                break;
            case PixelToaster::Key::Eight:
                persp_cube();
                break;
            case PixelToaster::Key::Nine:
                persp_multi_cubes();
                break;
            case PixelToaster::Key::Zero:
                persp_initials();
                break;
            case PixelToaster::Key::Escape:
                quit = true;
                break;
            default:
                printf("key not recognized: %d\n", key);
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

// unit radius cirle
void Application::circle()
{
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
    dl->gtBeginShape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        dl->gtVertex (xold, yold, 0);
        dl->gtVertex (x, y, 0);
        xold = x;
        yold = y;
    }

    dl->gtEndShape();
}

void Application::square()
{
  dl->gtBeginShape ();

  dl->gtVertex (-50, -50, 0);
  dl->gtVertex (-50, 50, 0);
  
  dl->gtVertex (-50, 50, 0);
  dl->gtVertex (50, 50, 0);

  dl->gtVertex (50, 50, 0);
  dl->gtVertex (50, -50, 0);

  dl->gtVertex (50, -50, 0);
  dl->gtVertex (-50, -50, 0);

  dl->gtEndShape();
}

void Application::cube()
{
    dl->gtBeginShape();
    
    // top square
    
    dl->gtVertex (-1.0, -1.0,  1.0);
    dl->gtVertex (-1.0,  1.0,  1.0);

    dl->gtVertex (-1.0,  1.0,  1.0);
    dl->gtVertex ( 1.0,  1.0,  1.0);

    dl->gtVertex ( 1.0,  1.0,  1.0);
    dl->gtVertex ( 1.0, -1.0,  1.0);

    dl->gtVertex ( 1.0, -1.0,  1.0);
    dl->gtVertex (-1.0, -1.0,  1.0);

    // bottom square
    
    dl->gtVertex (-1.0, -1.0, -1.0);
    dl->gtVertex (-1.0,  1.0, -1.0);
    
    dl->gtVertex (-1.0,  1.0, -1.0);
    dl->gtVertex ( 1.0,  1.0, -1.0);
    
    dl->gtVertex ( 1.0,  1.0, -1.0);
    dl->gtVertex ( 1.0, -1.0, -1.0);
    
    dl->gtVertex ( 1.0, -1.0, -1.0);
    dl->gtVertex (-1.0, -1.0, -1.0);
    
    // connect top to bottom
    
    dl->gtVertex (-1.0, -1.0, -1.0);
    dl->gtVertex (-1.0, -1.0,  1.0);
    
    dl->gtVertex (-1.0,  1.0, -1.0);
    dl->gtVertex (-1.0,  1.0,  1.0);
    
    dl->gtVertex ( 1.0,  1.0, -1.0);
    dl->gtVertex ( 1.0,  1.0,  1.0);
    
    dl->gtVertex ( 1.0, -1.0, -1.0);
    dl->gtVertex ( 1.0, -1.0,  1.0);
   
    dl->gtEndShape();
}

// draw a face by transforming circles;
void Application::face()
{
    // head
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.5, 0.5, 0);
    dl->matrix_lib_p->gtScale (0.4, 0.4, 1.0);
    circle();
    dl->matrix_lib_p->gtPopMatrix();

    // right eye
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.7, 0.7, 0.0);
    dl->matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    dl->matrix_lib_p->gtPopMatrix();

    // // left eye
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.3, 0.7, 0.0);
    dl->matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    dl->matrix_lib_p->gtPopMatrix();

    // nose
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.5, 0.5, 0.0);
    dl->matrix_lib_p->gtScale (0.07, 0.07, 1.0);
    circle();
    dl->matrix_lib_p->gtPopMatrix();

    // mouth
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.5, 0.25, 0.0);
    dl->matrix_lib_p->gtScale (0.2, 0.1, 1.0);
    circle();
    dl->matrix_lib_p->gtPopMatrix();
}

// draw several faces
void Application::faces()
{
    dl->matrix_lib_p->gtInitialize ();
    
    dl->gtOrtho (0, 1, 0, 1, -1, 1);
    
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.75, 0.25, 0.0);
    dl->matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    dl->matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    dl->matrix_lib_p->gtPopMatrix();
    
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.25, 0.25, 0.0);
    dl->matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    dl->matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    dl->matrix_lib_p->gtPopMatrix();
    
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.75, 0.75, 0.0);
    dl->matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    dl->matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    dl->matrix_lib_p->gtPopMatrix();
    
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate (0.25, 0.75, 0.0);
    dl->matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    dl->matrix_lib_p->gtRotateZ (30);
    dl->matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    dl->matrix_lib_p->gtPopMatrix();
} 

void Application::persp_initials()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtPerspective (60, -100, 100);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate(0, 0, -4);
    dl->matrix_lib_p->gtRotateZ(-45);
    dl->matrix_lib_p->gtRotateX(-45);
    dl->matrix_lib_p->gtRotateY(-45);

    dl->gtBeginShape();

    //Draw R
    dl->gtVertex(-1, 1, 0);
    dl->gtVertex(0, 1, 0);

    dl->gtVertex(-1, 1, 0);
    dl->gtVertex(-1, 0.5, 0);

    dl->gtVertex(0, 1, 0);
    dl->gtVertex(0, 0.5, 0);

    dl->gtVertex(-1, 0.5, 0);
    dl->gtVertex(-1, 0, 0);

    dl->gtVertex(-1, 0.5, 0);
    dl->gtVertex(0, 0.5, 0);

    dl->gtVertex(-1, 0.5, 0);
    dl->gtVertex(0, 0, 0);

    //draw S
    dl->gtVertex(0.2, 0.5, 0);
    dl->gtVertex(1, 0.5, 0);

    dl->gtVertex(0.2, 0.5, 0);
    dl->gtVertex(0.2, 0, 0);

    dl->gtVertex(0.2, 0, 0);
    dl->gtVertex(1, 0, 0);

    dl->gtVertex(1, 0, 0);
    dl->gtVertex(1, -1, 0);

    dl->gtVertex(1, -1, 0);
    dl->gtVertex(0.2, -1, 0);

    dl->gtEndShape();
    dl->matrix_lib_p->gtPopMatrix();
}

void Application::face_test()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (0, 1, 0, 1, -1, 1);
    face();
}

void Application::ortho_test()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void Application::ortho_test_scale()
{
    dl->matrix_lib_p->gtInitialize();
    dl->matrix_lib_p->gtScale(1,0.5,1);
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void Application::ortho_test_rotate()
{
    dl->matrix_lib_p->gtInitialize();
    dl->matrix_lib_p->gtRotateZ(20);
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void Application::ortho_cube()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-2, 2, -2, 2, -2, 2);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtRotateY(17);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
}

void Application::ortho_cube2()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-2, 2, -2, 2, -2, 2);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtRotateZ(5);
    dl->matrix_lib_p->gtRotateX(25);
    dl->matrix_lib_p->gtRotateY(20);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
}

void Application::persp_cube()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtPerspective (60, -100, 100);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate(0, 0, -4);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
}

void Application::persp_multi_cubes()
{
    dl->matrix_lib_p->gtInitialize();
    dl->gtPerspective (60, -100, 100);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate(0, 0, -20);
    dl->matrix_lib_p->gtRotateZ(5);
    dl->matrix_lib_p->gtRotateX(25);
    dl->matrix_lib_p->gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        dl->matrix_lib_p->gtPushMatrix();
        dl->matrix_lib_p->gtTranslate(delta, 0, 0);
        cube();
        dl->matrix_lib_p->gtPopMatrix();
        dl->matrix_lib_p->gtPushMatrix();
        dl->matrix_lib_p->gtTranslate(0, delta, 0);
        cube();
        dl->matrix_lib_p->gtPopMatrix();
        dl->matrix_lib_p->gtPushMatrix();
        dl->matrix_lib_p->gtTranslate(0, 0, delta);
        cube();
        dl->matrix_lib_p->gtPopMatrix();
    }    

    dl->matrix_lib_p->gtPopMatrix();
}
