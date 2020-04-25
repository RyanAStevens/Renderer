// Testing the Transformation, Projection and Line Drawing Routines

#include <matlib.h>
#include <drawlib.h>
#include <initials.h>

void setup()
{
    size (800, 800);
    background (255, 255, 255);  // white background
    stroke (0, 0, 0);            // black lines
    line(200, -200, 200, -600);
}

void draw()
{
}

// call the appropriate drawing routine, depending on which digit the user types
void keyPressed()
{
    background (255, 255, 255);
    /
    Switch(key)
    {
            case '1':
                ortho_test();
                break;
            case '2':
                ortho_test_scale();
                break;
            case '3':
                ortho_test_rotate();
                break;
            case '4':
                face_test();
                break;
            case '5':
                faces();
                break;
            case '6':
                ortho_cube();
                break;
            case '7':
                ortho_cube2();
                break;
            case '8':
                persp_cube();
                break;
            case '9':
                persp_multi_cubes();
                break;
            case '0':
                persp_initials();
                break;
            default:
                printf("key not recognized: %d\n", key);
    }
}

void ortho_test()
{
    gtInitialize();
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_scale()
{
    gtInitialize();
    gtScale(1,0.5,1);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_rotate()
{
    gtInitialize();
    gtRotateZ(20);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_cube()
{
    gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    gtPushMatrix();
    gtRotateY(17);
    cube();
    gtPopMatrix();
}

void ortho_cube2()
{
    gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    gtPushMatrix();
    gtRotateZ(5);
    gtRotateX(25);
    gtRotateY(20);
    cube();
    gtPopMatrix();
}

void persp_cube()
{
    gtInitialize();
    gtPerspective (60, -100, 100);
    gtPushMatrix();
    gtTranslate(0, 0, -4);
    cube();
    gtPopMatrix();
}

void persp_multi_cubes()
{
    gtInitialize();
    gtPerspective (60, -100, 100);
    
    gtPushMatrix();
    gtTranslate(0, 0, -20);
    gtRotateZ(5);
    gtRotateX(25);
    gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        gtPushMatrix();
        gtTranslate(delta, 0, 0);
        cube();
        gtPopMatrix();
        gtPushMatrix();
        gtTranslate(0, delta, 0);
        cube();
        gtPopMatrix();
        gtPushMatrix();
        gtTranslate(0, 0, delta);
        cube();
        gtPopMatrix();
    }    

    gtPopMatrix();
}

// unit radius cirle
void circle()
{
    steps = 65;
    xold = 1;
    yold = 0;
    gtBeginShape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        gtVertex (xold, yold, 0);
        gtVertex (x, y, 0);
        xold = x;
        yold = y;
    }

    gtEndShape();
}

void square()
{
  gtBeginShape ();

  gtVertex (-50, -50, 0);
  gtVertex (-50, 50, 0);
  
  gtVertex (-50, 50, 0);
  gtVertex (50, 50, 0);

  gtVertex (50, 50, 0);
  gtVertex (50, -50, 0);

  gtVertex (50, -50, 0);
  gtVertex (-50, -50, 0);

  gtEndShape();
}

void cube()
{
    gtBeginShape();
    
    // top square
    
    gtVertex (-1.0, -1.0,  1.0);
    gtVertex (-1.0,  1.0,  1.0);

    gtVertex (-1.0,  1.0,  1.0);
    gtVertex ( 1.0,  1.0,  1.0);

    gtVertex ( 1.0,  1.0,  1.0);
    gtVertex ( 1.0, -1.0,  1.0);

    gtVertex ( 1.0, -1.0,  1.0);
    gtVertex (-1.0, -1.0,  1.0);

    // bottom square
    
    gtVertex (-1.0, -1.0, -1.0);
    gtVertex (-1.0,  1.0, -1.0);
    
    gtVertex (-1.0,  1.0, -1.0);
    gtVertex ( 1.0,  1.0, -1.0);
    
    gtVertex ( 1.0,  1.0, -1.0);
    gtVertex ( 1.0, -1.0, -1.0);
    
    gtVertex ( 1.0, -1.0, -1.0);
    gtVertex (-1.0, -1.0, -1.0);
    
    // connect top to bottom
    
    gtVertex (-1.0, -1.0, -1.0);
    gtVertex (-1.0, -1.0,  1.0);
    
    gtVertex (-1.0,  1.0, -1.0);
    gtVertex (-1.0,  1.0,  1.0);
    
    gtVertex ( 1.0,  1.0, -1.0);
    gtVertex ( 1.0,  1.0,  1.0);
    
    gtVertex ( 1.0, -1.0, -1.0);
    gtVertex ( 1.0, -1.0,  1.0);
    
    gtEndShape();
}

void face_test()
{
    gtInitialize();
    gtOrtho (0, 1, 0, 1, -1, 1);
    face();
}

// draw a face by transforming circles;
void face()
{
    // head
    gtPushMatrix();
    gtTranslate (0.5, 0.5, 0);
    gtScale (0.4, 0.4, 1.0);
    circle();
    gtPopMatrix();

    // right eye
    gtPushMatrix();
    gtTranslate (0.7, 0.7, 0.0);
    gtScale (0.1, 0.1, 1.0);
    circle();
    gtPopMatrix();

    // // left eye
    gtPushMatrix();
    gtTranslate (0.3, 0.7, 0.0);
    gtScale (0.1, 0.1, 1.0);
    circle();
    gtPopMatrix();

    // nose
    gtPushMatrix();
    gtTranslate (0.5, 0.5, 0.0);
    gtScale (0.07, 0.07, 1.0);
    circle();
    gtPopMatrix();

    // mouth
    gtPushMatrix();
    gtTranslate (0.5, 0.25, 0.0);
    gtScale (0.2, 0.1, 1.0);
    circle();
    gtPopMatrix();
}

// draw several faces
void faces()
{
    gtInitialize ();
    
    gtOrtho (0, 1, 0, 1, -1, 1);
    
    gtPushMatrix();
    gtTranslate (0.75, 0.25, 0.0);
    gtScale (0.5, 0.5, 1.0);
    gtTranslate (-0.5, -0.5, 0.0);
    face();
    gtPopMatrix();
    
    gtPushMatrix();
    gtTranslate (0.25, 0.25, 0.0);
    gtScale (0.5, 0.5, 1.0);
    gtTranslate (-0.5, -0.5, 0.0);
    face();
    gtPopMatrix();
    
    gtPushMatrix();
    gtTranslate (0.75, 0.75, 0.0);
    gtScale (0.5, 0.5, 1.0);
    gtTranslate (-0.5, -0.5, 0.0);
    face();
    gtPopMatrix();
    
    gtPushMatrix();
    gtTranslate (0.25, 0.75, 0.0);
    gtScale (0.5, 0.5, 1.0);
    gtRotateZ (30);
    gtTranslate (-0.5, -0.5, 0.0);
    face();
    gtPopMatrix();
} 
