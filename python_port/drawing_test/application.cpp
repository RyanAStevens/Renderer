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
    printf("hello from Application::run\n");
    dl->create_window("Boom, Flip it!", WINDOW_HEIGHT, WINDOW_WIDTH, ORTHOGRAPHIC);
    
    printf("Application::run 1\n");
    // register listener
    dl->listen_window(this);
    printf("Application::run 2\n");
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
                printf("onKeyDown calling ortho_test\n");
                ortho_test();
                break;
            case PixelToaster::Key::Two:
                printf("onKeyDown calling ortho_test_scale\n");
                ortho_test_scale();
                break;
            case PixelToaster::Key::Three:
                printf("onKeyDown calling ortho_test_rotate\n");
                ortho_test_rotate();
                break;
            case PixelToaster::Key::Four:
                printf("onKeyDown calling face_test\n");
                face_test();
                break;
            case PixelToaster::Key::Five:
                printf("onKeyDown calling faces\n");
                faces();
                break;
            case PixelToaster::Key::Six:
                printf("onKeyDown calling ortho_cube\n");
                ortho_cube();
                break;
            case PixelToaster::Key::Seven:
                printf("onKeyDown calling ortho_cube2\n");
                ortho_cube2();
                break;
            case PixelToaster::Key::Eight:
                printf("onKeyDown calling persp_cube\n");
                persp_cube();
                break;
            case PixelToaster::Key::Nine:
                printf("onKeyDown calling persp_multi_cubes\n");
                persp_multi_cubes();
                break;
            case PixelToaster::Key::Zero:
                printf("onKeyDown calling persp_initials\n");
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
    printf("hello from circle\n");
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
    printf("goodbye from circle\n");
}

void Application::square()
{
    printf("hello from square\n");
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
    printf("goodbye from square\n");
}

void Application::cube()
{
    printf("hello from cube\n");
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
    printf("goodbye from cube\n");
}

// draw a face by transforming circles;
void Application::face()
{
    printf("hello from face\n");
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
    printf("goodbye from face\n");
}

// draw several faces
void Application::faces()
{
    printf("hello from faces\n");
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
    printf("goodbye from faces\n");
} 

void Application::persp_initials()
{
    printf("hello from persp_initials\n");
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
    printf("goodbye from persp_initials\n");
}

void Application::face_test()
{
    printf("hello from face_test\n");
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (0, 1, 0, 1, -1, 1);
    face();
    printf("goodbye from face_test\n");
}

void Application::ortho_test()
{
    printf("hello from ortho_test\n");
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test\n");
}

void Application::ortho_test_scale()
{
    printf("hello from ortho_test_scale\n");
    dl->matrix_lib_p->gtInitialize();
    dl->matrix_lib_p->gtScale(1,0.5,1);
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_scale\n");
}

void Application::ortho_test_rotate()
{
    printf("hello from ortho_test_rotate\n");
    dl->matrix_lib_p->gtInitialize();
    dl->matrix_lib_p->gtRotateZ(20);
    dl->gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_rotate\n");
}

void Application::ortho_cube()
{
    printf("hello from ortho_cube\n");
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-2, 2, -2, 2, -2, 2);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtRotateY(17);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube\n");
}

void Application::ortho_cube2()
{
    printf("hello from ortho_cube2\n");
    dl->matrix_lib_p->gtInitialize();
    dl->gtOrtho (-2, 2, -2, 2, -2, 2);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtRotateZ(5);
    dl->matrix_lib_p->gtRotateX(25);
    dl->matrix_lib_p->gtRotateY(20);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube2\n");
}

void Application::persp_cube()
{
    printf("hello from persp_cube\n");
    dl->matrix_lib_p->gtInitialize();
    dl->gtPerspective (60, -100, 100);
    dl->matrix_lib_p->gtPushMatrix();
    dl->matrix_lib_p->gtTranslate(0, 0, -4);
    cube();
    dl->matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_cube\n");
}

void Application::persp_multi_cubes()
{
    printf("hello from persp_multi_cubes\n");
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
    printf("goodbye from persp_multi_cubes\n");
}
