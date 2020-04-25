/*  
    Ryan Stevens
    CS 3451 Computer Graphics
    Georgia Institute of Technology
    Spring 2017

    file: initials.cpp
*/
// My initials drawn in perspective

#include <matlib.h>
#include <drawlib.h>

void persp_initials()
{
    gtInitialize();
    gtPerspective (60, -100, 100);
    gtPushMatrix();
    gtTranslate(0, 0, -4);
    gtRotateZ(-45);
    gtRotateX(-45);
    gtRotateY(-45);

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
    gtPopMatrix();
}
