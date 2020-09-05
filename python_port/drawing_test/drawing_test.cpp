// file: drawing_test.cpp
// Testing the Transformation, Projection and Line Drawing Routines

#include <matlib.h>
#include <drawlib.h>
#include <graphics_lib.h>

int main()
{  
    //printf("Hello, there from main.\n");
	int window_width = 1000;
	int window_height = 1000;
    MatLib matrix_lib = MatLib();
    GraphicsLib gl = GraphicsLib();
    DrawLib drawing_lib = DrawLib(&matrix_lib, &gl, window_width, window_height);
    //printf("hi 1\n");
    gl.create_window("Hello, there!", window_height, window_width, ORTHOGRAPHIC);
    //printf("hi 2\n");
    while(gl.window->open())
    {
		drawing_lib.gtBeginShape ();
     //   printf("hi 3\n");

		drawing_lib.gtVertex (-50, -50, 0);
		drawing_lib.gtVertex (-50, 50, 0);

		drawing_lib.gtVertex (-50, 50, 0);
		drawing_lib.gtVertex (50, 50, 0);

		drawing_lib.gtVertex (50, 50, 0);
		drawing_lib.gtVertex (50, -50, 0);

		drawing_lib.gtVertex (50, -50, 0);
		drawing_lib.gtVertex (-50, -50, 0);

   //     printf("hi 4\n");
		drawing_lib.gtEndShape();
    //    printf("hi 5\n");
		
		gl.window->update();
     //   printf("hi 6\n");
    }
 
    return 0;
}


/*
// unit radius cirle
void circle()
{
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
    drawing_lib.gtBeginShape();

    for(int i = 0; i <= steps; i++)
    {
        theta = 2 * 3.1415926535 * i / float(steps);
        x = cos(theta);
        y = sin(theta);
        drawing_lib.gtVertex (xold, yold, 0);
        drawing_lib.gtVertex (x, y, 0);
        xold = x;
        yold = y;
    }

    drawing_lib.gtEndShape();
}

void square()
{
  drawing_lib.gtBeginShape ();

  drawing_lib.gtVertex (-50, -50, 0);
  drawing_lib.gtVertex (-50, 50, 0);
  
  drawing_lib.gtVertex (-50, 50, 0);
  drawing_lib.gtVertex (50, 50, 0);

  drawing_lib.gtVertex (50, 50, 0);
  drawing_lib.gtVertex (50, -50, 0);

  drawing_lib.gtVertex (50, -50, 0);
  drawing_lib.gtVertex (-50, -50, 0);

  drawing_lib.gtEndShape();
}
void cube()
{
    drawing_lib.gtBeginShape();
    
    // top square
    
    drawing_lib.gtVertex (-1.0, -1.0,  1.0);
    drawing_lib.gtVertex (-1.0,  1.0,  1.0);

    drawing_lib.gtVertex (-1.0,  1.0,  1.0);
    drawing_lib.gtVertex ( 1.0,  1.0,  1.0);

    drawing_lib.gtVertex ( 1.0,  1.0,  1.0);
    drawing_lib.gtVertex ( 1.0, -1.0,  1.0);

    drawing_lib.gtVertex ( 1.0, -1.0,  1.0);
    drawing_lib.gtVertex (-1.0, -1.0,  1.0);

    // bottom square
    
    drawing_lib.gtVertex (-1.0, -1.0, -1.0);
    drawing_lib.gtVertex (-1.0,  1.0, -1.0);
    
    drawing_lib.gtVertex (-1.0,  1.0, -1.0);
    drawing_lib.gtVertex ( 1.0,  1.0, -1.0);
    
    drawing_lib.gtVertex ( 1.0,  1.0, -1.0);
    drawing_lib.gtVertex ( 1.0, -1.0, -1.0);
    
    drawing_lib.gtVertex ( 1.0, -1.0, -1.0);
    drawing_lib.gtVertex (-1.0, -1.0, -1.0);
    
    // connect top to bottom
    
    drawing_lib.gtVertex (-1.0, -1.0, -1.0);
    drawing_lib.gtVertex (-1.0, -1.0,  1.0);
    
    drawing_lib.gtVertex (-1.0,  1.0, -1.0);
    drawing_lib.gtVertex (-1.0,  1.0,  1.0);
    
    drawing_lib.gtVertex ( 1.0,  1.0, -1.0);
    drawing_lib.gtVertex ( 1.0,  1.0,  1.0);
    
    drawing_lib.gtVertex ( 1.0, -1.0, -1.0);
    drawing_lib.gtVertex ( 1.0, -1.0,  1.0);
   
    drawing_lib.gtEndShape();
}

// draw a face by transforming circles;
void face()
{
    // head
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.5, 0.5, 0);
    matrix_lib.gtScale (0.4, 0.4, 1.0);
    circle();
    matrix_lib.gtPopMatrix();

    // right eye
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.7, 0.7, 0.0);
    matrix_lib.gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib.gtPopMatrix();

    // // left eye
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.3, 0.7, 0.0);
    matrix_lib.gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib.gtPopMatrix();

    // nose
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.5, 0.5, 0.0);
    matrix_lib.gtScale (0.07, 0.07, 1.0);
    circle();
    matrix_lib.gtPopMatrix();

    // mouth
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.5, 0.25, 0.0);
    matrix_lib.gtScale (0.2, 0.1, 1.0);
    circle();
    matrix_lib.gtPopMatrix();
}

// draw several faces
void faces()
{
    matrix_lib.gtInitialize ();
    
    drawing_lib.gtOrtho (0, 1, 0, 1, -1, 1);
    
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.75, 0.25, 0.0);
    matrix_lib.gtScale (0.5, 0.5, 1.0);
    matrix_lib.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib.gtPopMatrix();
    
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.25, 0.25, 0.0);
    matrix_lib.gtScale (0.5, 0.5, 1.0);
    matrix_lib.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib.gtPopMatrix();
    
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.75, 0.75, 0.0);
    matrix_lib.gtScale (0.5, 0.5, 1.0);
    matrix_lib.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib.gtPopMatrix();
    
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate (0.25, 0.75, 0.0);
    matrix_lib.gtScale (0.5, 0.5, 1.0);
    matrix_lib.gtRotateZ (30);
    matrix_lib.gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib.gtPopMatrix();
} 

void persp_initials()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtPerspective (60, -100, 100);
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate(0, 0, -4);
    matrix_lib.gtRotateZ(-45);
    matrix_lib.gtRotateX(-45);
    matrix_lib.gtRotateY(-45);

    drawing_lib.gtBeginShape();

    //Draw R
    drawing_lib.gtVertex(-1, 1, 0);
    drawing_lib.gtVertex(0, 1, 0);

    drawing_lib.gtVertex(-1, 1, 0);
    drawing_lib.gtVertex(-1, 0.5, 0);

    drawing_lib.gtVertex(0, 1, 0);
    drawing_lib.gtVertex(0, 0.5, 0);

    drawing_lib.gtVertex(-1, 0.5, 0);
    drawing_lib.gtVertex(-1, 0, 0);

    drawing_lib.gtVertex(-1, 0.5, 0);
    drawing_lib.gtVertex(0, 0.5, 0);

    drawing_lib.gtVertex(-1, 0.5, 0);
    drawing_lib.gtVertex(0, 0, 0);

    //draw S
    drawing_lib.gtVertex(0.2, 0.5, 0);
    drawing_lib.gtVertex(1, 0.5, 0);

    drawing_lib.gtVertex(0.2, 0.5, 0);
    drawing_lib.gtVertex(0.2, 0, 0);

    drawing_lib.gtVertex(0.2, 0, 0);
    drawing_lib.gtVertex(1, 0, 0);

    drawing_lib.gtVertex(1, 0, 0);
    drawing_lib.gtVertex(1, -1, 0);

    drawing_lib.gtVertex(1, -1, 0);
    drawing_lib.gtVertex(0.2, -1, 0);

    drawing_lib.gtEndShape();
    matrix_lib.gtPopMatrix();
}

void face_test()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtOrtho (0, 1, 0, 1, -1, 1);
    face();
}

void ortho_test()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_scale()
{
    matrix_lib.gtInitialize();
    matrix_lib.gtScale(1,0.5,1);
    drawing_lib.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_test_rotate()
{
    matrix_lib.gtInitialize();
    matrix_lib.gtRotateZ(20);
    drawing_lib.gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
}

void ortho_cube()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib.gtPushMatrix();
    matrix_lib.gtRotateY(17);
    cube();
    matrix_lib.gtPopMatrix();
}

void ortho_cube2()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib.gtPushMatrix();
    matrix_lib.gtRotateZ(5);
    matrix_lib.gtRotateX(25);
    matrix_lib.gtRotateY(20);
    cube();
    matrix_lib.gtPopMatrix();
}

void persp_cube()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtPerspective (60, -100, 100);
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate(0, 0, -4);
    cube();
    matrix_lib.gtPopMatrix();
}

void persp_multi_cubes()
{
    matrix_lib.gtInitialize();
    drawing_lib.gtPerspective (60, -100, 100);
    matrix_lib.gtPushMatrix();
    matrix_lib.gtTranslate(0, 0, -20);
    matrix_lib.gtRotateZ(5);
    matrix_lib.gtRotateX(25);
    matrix_lib.gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        matrix_lib.gtPushMatrix();
        matrix_lib.gtTranslate(delta, 0, 0);
        cube();
        matrix_lib.gtPopMatrix();
        matrix_lib.gtPushMatrix();
        matrix_lib.gtTranslate(0, delta, 0);
        cube();
        matrix_lib.gtPopMatrix();
        matrix_lib.gtPushMatrix();
        matrix_lib.gtTranslate(0, 0, delta);
        cube();
        matrix_lib.gtPopMatrix();
    }    

    matrix_lib.gtPopMatrix();
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
*/
