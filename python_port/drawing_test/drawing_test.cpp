// file: drawing_test.cpp
// Testing the Transformation, Projection and Line Drawing Routines

#include <matlib.h>
#include <drawlib.h>
#include <PixelToaster.h>

MatLib matrix_functions = MatLib();
DrawLib drawing_functions = DrawLib();

// unit radius cirle
void circle()
{
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
    drawing_functions.gtBeginShape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        drawing_functions.gtVertex (xold, yold, 0);
        drawing_functions.gtVertex (x, y, 0);
        xold = x;
        yold = y;
    }

    drawing_functions.gtEndShape();
}

void square()
{
  drawing_functions.gtBeginShape ();

  drawing_functions.gtVertex (-50, -50, 0);
  drawing_functions.gtVertex (-50, 50, 0);
  
  drawing_functions.gtVertex (-50, 50, 0);
  drawing_functions.gtVertex (50, 50, 0);

  drawing_functions.gtVertex (50, 50, 0);
  drawing_functions.gtVertex (50, -50, 0);

  drawing_functions.gtVertex (50, -50, 0);
  drawing_functions.gtVertex (-50, -50, 0);

  drawing_functions.gtEndShape();
}

void cube()
{
    drawing_functions.gtBeginShape();
    
    // top square
    
    drawing_functions.gtVertex (-1.0, -1.0,  1.0);
    drawing_functions.gtVertex (-1.0,  1.0,  1.0);

    drawing_functions.gtVertex (-1.0,  1.0,  1.0);
    drawing_functions.gtVertex ( 1.0,  1.0,  1.0);

    drawing_functions.gtVertex ( 1.0,  1.0,  1.0);
    drawing_functions.gtVertex ( 1.0, -1.0,  1.0);

    drawing_functions.gtVertex ( 1.0, -1.0,  1.0);
    drawing_functions.gtVertex (-1.0, -1.0,  1.0);

    // bottom square
    
    drawing_functions.gtVertex (-1.0, -1.0, -1.0);
    drawing_functions.gtVertex (-1.0,  1.0, -1.0);
    
    drawing_functions.gtVertex (-1.0,  1.0, -1.0);
    drawing_functions.gtVertex ( 1.0,  1.0, -1.0);
    
    drawing_functions.gtVertex ( 1.0,  1.0, -1.0);
    drawing_functions.gtVertex ( 1.0, -1.0, -1.0);
    
    drawing_functions.gtVertex ( 1.0, -1.0, -1.0);
    drawing_functions.gtVertex (-1.0, -1.0, -1.0);
    
    // connect top to bottom
    
    drawing_functions.gtVertex (-1.0, -1.0, -1.0);
    drawing_functions.gtVertex (-1.0, -1.0,  1.0);
    
    drawing_functions.gtVertex (-1.0,  1.0, -1.0);
    drawing_functions.gtVertex (-1.0,  1.0,  1.0);
    
    drawing_functions.gtVertex ( 1.0,  1.0, -1.0);
    drawing_functions.gtVertex ( 1.0,  1.0,  1.0);
    
    drawing_functions.gtVertex ( 1.0, -1.0, -1.0);
    drawing_functions.gtVertex ( 1.0, -1.0,  1.0);
   
    drawing_functions.gtEndShape();
}

// draw a face by transforming circles;
void face()
{
    // head
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.5, 0.5, 0);
    matrix_functions.gtScale (0.4, 0.4, 1.0);
    circle();
    matrix_functions.gtPopMatrix();

    // right eye
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.7, 0.7, 0.0);
    matrix_functions.gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_functions.gtPopMatrix();

    // // left eye
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.3, 0.7, 0.0);
    matrix_functions.gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_functions.gtPopMatrix();

    // nose
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.5, 0.5, 0.0);
    matrix_functions.gtScale (0.07, 0.07, 1.0);
    circle();
    matrix_functions.gtPopMatrix();

    // mouth
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.5, 0.25, 0.0);
    matrix_functions.gtScale (0.2, 0.1, 1.0);
    circle();
    matrix_functions.gtPopMatrix();
}

// draw several faces
void faces()
{
    matrix_functions.gtInitialize ();
    
    drawing_functions.gtOrtho (0, 1, 0, 1, -1, 1);
    
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.75, 0.25, 0.0);
    matrix_functions.gtScale (0.5, 0.5, 1.0);
    matrix_functions.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_functions.gtPopMatrix();
    
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.25, 0.25, 0.0);
    matrix_functions.gtScale (0.5, 0.5, 1.0);
    matrix_functions.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_functions.gtPopMatrix();
    
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.75, 0.75, 0.0);
    matrix_functions.gtScale (0.5, 0.5, 1.0);
    matrix_functions.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_functions.gtPopMatrix();
    
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate (0.25, 0.75, 0.0);
    matrix_functions.gtScale (0.5, 0.5, 1.0);
    matrix_functions.gtRotateZ (30);
    matrix_functions.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_functions.gtPopMatrix();
} 

void persp_initials()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtPerspective (60, -100, 100);
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate(0, 0, -4);
    matrix_functions.gtRotateZ(-45);
    matrix_functions.gtRotateX(-45);
    matrix_functions.gtRotateY(-45);

    drawing_functions.gtBeginShape();

    //Draw R
    drawing_functions.gtVertex(-1, 1, 0);
    drawing_functions.gtVertex(0, 1, 0);

    drawing_functions.gtVertex(-1, 1, 0);
    drawing_functions.gtVertex(-1, 0.5, 0);

    drawing_functions.gtVertex(0, 1, 0);
    drawing_functions.gtVertex(0, 0.5, 0);

    drawing_functions.gtVertex(-1, 0.5, 0);
    drawing_functions.gtVertex(-1, 0, 0);

    drawing_functions.gtVertex(-1, 0.5, 0);
    drawing_functions.gtVertex(0, 0.5, 0);

    drawing_functions.gtVertex(-1, 0.5, 0);
    drawing_functions.gtVertex(0, 0, 0);

    //draw S
    drawing_functions.gtVertex(0.2, 0.5, 0);
    drawing_functions.gtVertex(1, 0.5, 0);

    drawing_functions.gtVertex(0.2, 0.5, 0);
    drawing_functions.gtVertex(0.2, 0, 0);

    drawing_functions.gtVertex(0.2, 0, 0);
    drawing_functions.gtVertex(1, 0, 0);

    drawing_functions.gtVertex(1, 0, 0);
    drawing_functions.gtVertex(1, -1, 0);

    drawing_functions.gtVertex(1, -1, 0);
    drawing_functions.gtVertex(0.2, -1, 0);

    drawing_functions.gtEndShape();
    matrix_functions.gtPopMatrix();
}

void face_test()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtOrtho (0, 1, 0, 1, -1, 1);
    face();
}

void ortho_test()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_scale()
{
    matrix_functions.gtInitialize();
    matrix_functions.gtScale(1,0.5,1);
    drawing_functions.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_rotate()
{
    matrix_functions.gtInitialize();
    matrix_functions.gtRotateZ(20);
    drawing_functions.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_cube()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_functions.gtPushMatrix();
    matrix_functions.gtRotateY(17);
    cube();
    matrix_functions.gtPopMatrix();
}

void ortho_cube2()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_functions.gtPushMatrix();
    matrix_functions.gtRotateZ(5);
    matrix_functions.gtRotateX(25);
    matrix_functions.gtRotateY(20);
    cube();
    matrix_functions.gtPopMatrix();
}

void persp_cube()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtPerspective (60, -100, 100);
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate(0, 0, -4);
    cube();
    matrix_functions.gtPopMatrix();
}

void persp_multi_cubes()
{
    matrix_functions.gtInitialize();
    drawing_functions.gtPerspective (60, -100, 100);
    matrix_functions.gtPushMatrix();
    matrix_functions.gtTranslate(0, 0, -20);
    matrix_functions.gtRotateZ(5);
    matrix_functions.gtRotateX(25);
    matrix_functions.gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        matrix_functions.gtPushMatrix();
        matrix_functions.gtTranslate(delta, 0, 0);
        cube();
        matrix_functions.gtPopMatrix();
        matrix_functions.gtPushMatrix();
        matrix_functions.gtTranslate(0, delta, 0);
        cube();
        matrix_functions.gtPopMatrix();
        matrix_functions.gtPushMatrix();
        matrix_functions.gtTranslate(0, 0, delta);
        cube();
        matrix_functions.gtPopMatrix();
    }    

    matrix_functions.gtPopMatrix();
}

// call the appropriate drawing routine, depending on which digit the user types
void keyPressed(char key)
{
    switch(key)
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

int main()
{
}
