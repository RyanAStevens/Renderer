// unit radius cirle
void circle()
{
    printf("hello from circle\n");
    int steps = 65;
    int x = 0;
    int y = 0;
    int xold = 1;
    int yold = 0;
    float theta = 0.0f;
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
    printf("goodbye from circle\n");
}

void square()
{
    printf("hello from square\n");
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
    printf("goodbye from square\n");
}

void cube()
{
    printf("hello from cube\n");
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
    printf("goodbye from cube\n");
}

// draw a face by transforming circles;
void face()
{
    printf("hello from face\n");
    // head
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.5, 0);
    matrix_lib_p->gtScale (0.4, 0.4, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // right eye
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.7, 0.7, 0.0);
    matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // // left eye
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.3, 0.7, 0.0);
    matrix_lib_p->gtScale (0.1, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // nose
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.5, 0.0);
    matrix_lib_p->gtScale (0.07, 0.07, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();

    // mouth
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.5, 0.25, 0.0);
    matrix_lib_p->gtScale (0.2, 0.1, 1.0);
    circle();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from face\n");
}

// draw several faces
void faces()
{
    printf("hello from faces\n");
    matrix_lib_p->gtInitialize ();
    
    gtOrtho (0, 1, 0, 1, -1, 1);
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.75, 0.25, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.25, 0.25, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.75, 0.75, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate (0.25, 0.75, 0.0);
    matrix_lib_p->gtScale (0.5, 0.5, 1.0);
    matrix_lib_p->gtRotateZ (30);
    matrix_lib_p->gtTranslate (-0.5, -0.5, 0.0);
    face();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from faces\n");
} 

void persp_initials()
{
    printf("hello from persp_initials\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -4);
    matrix_lib_p->gtRotateZ(-45);
    matrix_lib_p->gtRotateX(-45);
    matrix_lib_p->gtRotateY(-45);

    gtBeginShape();

    //Draw R
    gtVertex(-1, 1, 0);
    gtVertex(0, 1, 0);

    gtVertex(-1, 1, 0);
    gtVertex(-1, 0.5, 0);

    gtVertex(0, 1, 0);
    gtVertex(0, 0.5, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(-1, 0, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(0, 0.5, 0);

    gtVertex(-1, 0.5, 0);
    gtVertex(0, 0, 0);

    //draw S
    gtVertex(0.2, 0.5, 0);
    gtVertex(1, 0.5, 0);

    gtVertex(0.2, 0.5, 0);
    gtVertex(0.2, 0, 0);

    gtVertex(0.2, 0, 0);
    gtVertex(1, 0, 0);

    gtVertex(1, 0, 0);
    gtVertex(1, -1, 0);

    gtVertex(1, -1, 0);
    gtVertex(0.2, -1, 0);

    gtEndShape();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_initials\n");
}

void face_test()
{
    printf("hello from face_test\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (0, 1, 0, 1, -1, 1);
    face();
    printf("goodbye from face_test\n");
}

void ortho_test()
{
    printf("hello from ortho_test\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test\n");
}

void ortho_test_scale()
{
    printf("hello from ortho_test_scale\n");
    matrix_lib_p->gtInitialize();
    matrix_lib_p->gtScale(1,0.5,1);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_scale\n");
}

void ortho_test_rotate()
{
    printf("hello from ortho_test_rotate\n");
    matrix_lib_p->gtInitialize();
    matrix_lib_p->gtRotateZ(20);
    gtOrtho (-100, 100, -100, 100, -100, 100);
    square();
    printf("goodbye from ortho_test_rotate\n");
}

void ortho_cube()
{
    printf("hello from ortho_cube\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtRotateY(17);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube\n");
}

void ortho_cube2()
{
    printf("hello from ortho_cube2\n");
    matrix_lib_p->gtInitialize();
    gtOrtho (-2, 2, -2, 2, -2, 2);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtRotateZ(5);
    matrix_lib_p->gtRotateX(25);
    matrix_lib_p->gtRotateY(20);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from ortho_cube2\n");
}

void persp_cube()
{
    printf("hello from persp_cube\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -4);
    cube();
    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_cube\n");
}

void persp_multi_cubes()
{
    printf("hello from persp_multi_cubes\n");
    matrix_lib_p->gtInitialize();
    gtPerspective (60, -100, 100);
    matrix_lib_p->gtPushMatrix();
    matrix_lib_p->gtTranslate(0, 0, -20);
    matrix_lib_p->gtRotateZ(5);
    matrix_lib_p->gtRotateX(25);
    matrix_lib_p->gtRotateY(20);
    
    // draw several cubes in three lines (x, y, z)
    for(int delta = -12; delta <= 13; delta += 3)
    {
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(delta, 0, 0);
        cube();
        matrix_lib_p->gtPopMatrix();
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(0, delta, 0);
        cube();
        matrix_lib_p->gtPopMatrix();
        matrix_lib_p->gtPushMatrix();
        matrix_lib_p->gtTranslate(0, 0, delta);
        cube();
        matrix_lib_p->gtPopMatrix();
    }    

    matrix_lib_p->gtPopMatrix();
    printf("goodbye from persp_multi_cubes\n");
}
